#include "search.hpp"
#include "board.hpp"
#include "common.hpp"
#include "movegen.hpp"
#include "movepick.hpp"
#include "tm.hpp"
#include "uci.hpp"
#include "util/types.hpp"
#include <array>
#include <iostream>
#include <limits>

namespace Clockwork {
namespace Search {

Value mated_in(i32 ply) {
    return -VALUE_MATED + ply;
}

Worker::Worker(TT& tt, ThreadData& td) :
    m_tt(tt),
    m_td(td) {
}


bool Worker::check_tm_hard_limit() {
    time::TimePoint now = time::Clock::now();
    if (now >= m_search_limits.hard_time_limit) {
        m_stopped = true;
        return true;
    }
    return false;
}

void Worker::launch_search(Position            root_position,
                           RepetitionInfo      repetition_info,
                           UCI::SearchSettings settings) {
    // Search setup
    m_search_start = time::Clock::now();
    search_nodes   = 0;
    m_stopped      = false;

    // Get a copy of the repetition_info to futureproof for multithreaded search
    m_repetition_info = repetition_info;

    // TODO: time setup only needed by the main worker thread
    m_search_limits = {.hard_time_limit = TM::compute_hard_limit(m_search_start, settings,
                                                                 root_position.active_color()),
                       .soft_node_limit = settings.soft_nodes > 0 ? settings.soft_nodes
                                                                  : std::numeric_limits<u64>::max(),
                       .hard_node_limit = settings.hard_nodes > 0 ? settings.hard_nodes
                                                                  : std::numeric_limits<u64>::max(),
                       .depth_limit     = settings.depth > 0 ? settings.depth : MAX_PLY};

    m_td.history.clear();

    // Run iterative deepening search
    Move best_move = iterative_deepening(root_position);

    // Print (and make sure to flush) the best move
    std::cout << "bestmove " << best_move << std::endl;
}

Move Worker::iterative_deepening(Position root_position) {

    std::array<Stack, MAX_PLY + 1> ss;
    std::array<Move, MAX_PLY + 1>  pv;
    Value                          alpha = -VALUE_INF, beta = +VALUE_INF;

    Depth root_depth = m_search_limits.depth_limit;
    for (u32 i = 0; i < static_cast<u32>(MAX_PLY); i++) {
        ss[i].pv = &pv[i];
    }

    Depth last_search_depth = 0;
    Value last_search_score = -VALUE_INF;
    Move  last_best_move    = Move::none();

    const auto print_info_line = [&] {
        // Lambda to convert internal units score to uci score. TODO: add eval rescaling here once we get one
        auto format_score = [](Value score) {
            if (score < -VALUE_WIN && score > -VALUE_MATED) {
                return "mate " + std::to_string(-(VALUE_MATED + score + 2) / 2);
            }
            if (score > VALUE_WIN && score < VALUE_MATED) {
                return "mate " + std::to_string((VALUE_MATED + 1 - score) / 2);
            }
            return "cp " + std::to_string(score);
        };

        // Get current time
        auto curr_time = time::Clock::now();

        std::cout << std::dec << "info depth " << last_search_depth << " score "
                  << format_score(last_search_score) << " nodes " << search_nodes << " nps "
                  << time::nps(search_nodes, curr_time - m_search_start) << " pv " << last_best_move
                  << std::endl;
    };

    for (Depth search_depth = 1;; search_depth++) {
        // Call search
        Value score = search(root_position, &ss[0], alpha, beta, search_depth, 0);

        // If m_stopped is true, then the search exited early. Discard the results for this depth.
        if (m_stopped) {
            break;
        }

        // Store information only if the last iterative deepening search completed
        last_search_depth = search_depth;
        last_search_score = score;
        last_best_move    = *ss[0].pv;

        // Check depth limit
        if (search_depth >= root_depth) {
            break;
        }
        // Check soft node limit
        if (search_nodes >= m_search_limits.soft_node_limit) {
            break;
        }
        // TODO: add any soft time limit check here

        print_info_line();
    }

    // Print last info line
    // This ensures we output our last value of search_nodes before termination, allowing for accurate search reproduction.
    print_info_line();

    return last_best_move;
}

Value Worker::search(Position& pos, Stack* ss, Value alpha, Value beta, Depth depth, i32 ply) {
    if (depth <= 0) {
        return quiesce(pos, ss, alpha, beta, ply);
    }

    const bool ROOT_NODE = ply == 0;

    // TODO: search nodes limit condition here
    // ...
    search_nodes++;

    // Draw checks
    if (!ROOT_NODE) {
        // Repetition check
        if (m_repetition_info.detect_repetition(ply)) {
            return 0;
        }
        // 50 mr check
        if (pos.get_50mr_counter() >= 100) {
            return 0;
        }
    }

    // Return eval if we exceed the max ply.
    if (ply >= MAX_PLY) {
        return evaluate(pos);
    }

    // Check for hard time limit
    // TODO: add control for being main search thread here
    if ((search_nodes & 2047) == 0 && check_tm_hard_limit()) {
        return 0;
    }

    // Check for hard nodes limit
    if (search_nodes >= m_search_limits.hard_node_limit) {
        m_stopped = true;
        return 0;
    }

    auto tt_data = m_tt.probe(pos, ply);
    if (!ROOT_NODE && tt_data && tt_data->depth >= depth
        && (tt_data->bound == Bound::Exact
            || (tt_data->bound == Bound::Lower && tt_data->score >= beta)
            || (tt_data->bound == Bound::Upper && tt_data->score <= alpha))) {
        return tt_data->score;
    }

    bool  is_in_check = pos.is_in_check();
    Value static_eval = is_in_check ? -VALUE_INF : evaluate(pos);

    if (!ROOT_NODE && !is_in_check && depth <= 6 && static_eval >= beta + 80 * depth) {
        return static_eval;
    }

    if (!ROOT_NODE && !is_in_check && depth >= 3) {
        int      R         = 3;
        Position pos_after = pos.null_move();

        m_repetition_info.push(pos_after.get_hash_key(), true);

        Value value = -search(pos_after, ss + 1, -beta, -beta + 1, depth - R, ply + 1);

        m_repetition_info.pop();

        if (value >= beta) {
            return value > VALUE_WIN ? beta : value;
        }
    }

    MovePicker moves{pos, m_td.history, tt_data ? tt_data->move : Move::none(), ss->killer};
    Move       best_move  = Move::none();
    Value      best_value = -VALUE_INF;

    // Clear child's killer move.
    (ss + 1)->killer = Move::none();

    // Iterate over the move list
    for (Move m = moves.next(); m != Move::none(); m = moves.next()) {
        // Do move
        Position pos_after = pos.move(m);

        // Put hash into repetition table. TODO: encapsulate this and any other future adjustment to do "on move" into a proper function
        m_repetition_info.push(pos_after.get_hash_key(), pos_after.is_reversible(m));

        // Get search value
        Depth new_depth = depth - 1 + pos_after.is_in_check();
        Value value     = -search(pos_after, ss + 1, -beta, -alpha, new_depth, ply + 1);

        // TODO: encapsulate this and any other future adjustment to do "on going back" into a proper function
        m_repetition_info.pop();

        if (m_stopped) {
            return 0;
        }

        if (value > best_value) {
            best_value = value;
            if (ply == 0) {
                ss->pv[ply] = m;  // No pv update for now, just bestmove
            }

            if (value > alpha) {
                alpha     = value;
                best_move = m;

                if (value >= beta) {
                    break;
                }
            }
        }
    }

    if (best_value >= beta && quiet_move(best_move)) {
        ss->killer = best_move;

        m_td.history.update_quiet_stats(pos, best_move, depth * depth);
    }

    // Checkmate / Stalemate check
    if (best_value == -VALUE_INF) {
        if (pos.is_in_check()) {
            return mated_in(ply);
        } else {
            return 0;
        }
    }

    Bound bound = best_value >= beta        ? Bound::Lower
                : best_move != Move::none() ? Bound::Exact
                                            : Bound::Upper;
    m_tt.store(pos, ply, best_move, best_value, depth, bound);

    return best_value;
}

Value Worker::quiesce(Position& pos, Stack* ss, Value alpha, Value beta, i32 ply) {
    search_nodes++;

    // 50 mr check
    if (pos.get_50mr_counter() >= 100) {
        return 0;
    }

    // Return eval if we exceed the max ply.
    if (ply >= MAX_PLY) {
        return evaluate(pos);
    }

    // Check for hard time limit
    if ((search_nodes & 2047) == 0 && check_tm_hard_limit()) {
        return 0;
    }

    // Check for hard nodes limit
    if (search_nodes >= m_search_limits.hard_node_limit) {
        m_stopped = true;
        return 0;
    }

    bool  is_in_check = pos.is_in_check();
    Value static_eval = is_in_check ? -VALUE_INF : evaluate(pos);

    // Stand pat
    if (static_eval >= beta) {
        return static_eval;
    }
    alpha = std::max(alpha, static_eval);

    MovePicker moves{pos, m_td.history};
    if (!is_in_check) {
        moves.skip_quiets();
    }

    Value best_value     = static_eval;
    u32   moves_searched = 0;

    // Iterate over the move list
    for (Move m = moves.next(); m != Move::none(); m = moves.next()) {
        // Do move
        Position pos_after = pos.move(m);
        moves_searched++;

        // Put hash into repetition table. TODO: encapsulate this and any other future adjustment to do "on move" into a proper function
        m_repetition_info.push(pos_after.get_hash_key(), pos_after.is_reversible(m));

        // Get search value
        Value value = -quiesce(pos_after, ss + 1, -beta, -alpha, ply + 1);

        // TODO: encapsulate this and any other future adjustment to do "on going back" into a proper function
        m_repetition_info.pop();

        if (m_stopped) {
            return 0;
        }

        if (value > best_value) {
            best_value = value;

            if (value > alpha) {
                alpha = value;

                if (value >= beta) {
                    break;
                }
            }
        }
    }

    // Checkmate check
    if (is_in_check && moves_searched == 0) {
        return mated_in(ply);
    }

    return best_value;
}

Value Worker::evaluate(const Position& pos) {
    const Color us   = pos.active_color();
    const Color them = invert(us);
    return 100 * (pos.piece_count(us, PieceType::Pawn) - pos.piece_count(them, PieceType::Pawn))
         + 330 * (pos.piece_count(us, PieceType::Knight) - pos.piece_count(them, PieceType::Knight))
         + 370 * (pos.piece_count(us, PieceType::Bishop) - pos.piece_count(them, PieceType::Bishop))
         + 550 * (pos.piece_count(us, PieceType::Rook) - pos.piece_count(them, PieceType::Rook))
         + 1000 * (pos.piece_count(us, PieceType::Queen) - pos.piece_count(them, PieceType::Queen))
         + static_cast<i32>(search_nodes & 7) - 3 + 10;
}
}
}
