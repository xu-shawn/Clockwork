#include <ranges>

#include "bitboard.hpp"
#include "common.hpp"
#include "position.hpp"
#include "psqt_state.hpp"

#include "evaluation.hpp"

#include "eval_types.hpp"
#include "square.hpp"
#include "util/bit.hpp"

namespace Clockwork {

// clang-format off
const PScore PAWN_MAT   = S(296,534);
const PScore KNIGHT_MAT = S(865,994);
const PScore BISHOP_MAT = S(882,1078);
const PScore ROOK_MAT   = S(1285,1793);
const PScore QUEEN_MAT  = S(2779,3350);
const PScore TEMPO_VAL  = S(30,16);

const PScore BISHOP_PAIR_VAL  = S(49,207);
const PScore DOUBLED_PAWN_VAL = S(-71,-118);

const PScore RFB = S(14,0);

const std::array<PScore, 9> KNIGHT_MOBILITY = {
    S(-157,-200), S(-74,-111), S(-32,-25), S(-21,13), S(9,35), S(33,51), S(54,51), S(84,15), S(129,-59),
};
const std::array<PScore, 14> BISHOP_MOBILITY = {
    S(-149,-190), S(-105,-124), S(-56,-84), S(-27,-55), S(-5,-8), S(18,0), S(36,5), S(41,24), S(61,25), S(68,16), S(102,0), S(210,-84), S(189,-59), S(287,-147),
};
const std::array<PScore, 15> ROOK_MOBILITY = {
    S(-92,-84), S(-69,-33), S(-50,-24), S(-45,-27), S(-45,1), S(-21,20), S(-8,18), S(9,21), S(18,42), S(44,39), S(58,38), S(82,39), S(99,30), S(100,29), S(238,-82),
};
const std::array<PScore, 28> QUEEN_MOBILITY = {
    S(-209,-35), S(-96,-495), S(-95,-496), S(-117,-329), S(-114,-227), S(-104,-148), S(-92,-152), S(-103,-50), S(-87,-58), S(-73,-50), S(-82,41), S(-66,50), S(-53,32), S(-43,56), S(-35,65), S(-40,98), S(-45,93), S(-20,66), S(13,44), S(56,-4), S(143,-62), S(159,-94), S(192,-107), S(489,-397), S(474,-313), S(1120,-618), S(380,-198), S(909,-610),
};
const std::array<PScore, 9> KING_MOBILITY = {
    S(236,294), S(118,376), S(97,368), S(71,399), S(33,393), S(-5,385), S(-24,388), S(-34,349), S(27,250),
};

const std::array<PScore, 48> PAWN_PSQT = {
    S(-187,459),    S(8,419),       S(65,454),      S(216,216),     S(171,222),     S(230,312),     S(82,346),      S(171,330),     //
    S(-28,95),      S(127,158),     S(76,45),       S(181,-27),     S(102,-18),     S(5,42),        S(-62,92),      S(-122,55),     //
    S(-55,-69),     S(-18,-64),     S(-41,-108),    S(-40,-148),    S(-55,-127),    S(-107,-128),   S(-141,-58),    S(-185,-35),    //
    S(-39,-176),    S(16,-138),     S(-42,-175),    S(-68,-165),    S(-71,-188),    S(-122,-172),   S(-169,-90),    S(-210,-105),   //
    S(2,-217),      S(102,-203),    S(-3,-166),     S(-72,-144),    S(-94,-151),    S(-148,-154),   S(-154,-114),   S(-205,-127),   //
    S(-48,-211),    S(149,-213),    S(32,-167),     S(-91,-102),    S(-131,-150),   S(-155,-142),   S(-169,-98),    S(-205,-123),   //
};
const std::array<PScore, 64> KNIGHT_PSQT = {
    S(-375,-193),   S(0,-139),      S(-498,227),    S(81,14),       S(-198,102),    S(-255,136),    S(-269,-60),    S(-489,-15),    //
    S(47,-92),      S(64,53),       S(250,-53),     S(102,39),      S(178,49),      S(131,-54),     S(-34,-34),     S(35,-90),      //
    S(71,2),        S(120,93),      S(291,83),      S(232,51),      S(195,74),      S(81,84),       S(10,82),       S(-98,14),      //
    S(145,-12),     S(79,66),       S(180,76),      S(118,95),      S(145,98),      S(60,101),      S(-20,46),      S(-41,41),      //
    S(8,32),        S(140,29),      S(69,76),       S(58,86),       S(25,108),      S(11,104),      S(-35,65),      S(-70,-38),     //
    S(-60,3),       S(-1,-23),      S(5,-14),       S(32,51),       S(28,55),       S(-85,37),      S(-67,-4),      S(-136,-21),    //
    S(-67,31),      S(-33,14),      S(-72,3),       S(-24,14),      S(-39,-5),      S(-106,6),      S(-119,-23),    S(-180,-105),   //
    S(-242,22),     S(-80,-71),     S(-66,-57),     S(-25,-23),     S(-60,-23),     S(-74,-121),    S(-162,-10),    S(-269,-13),    //
};
const std::array<PScore, 64> BISHOP_PSQT = {
    S(-153,70),     S(-60,16),      S(-514,109),    S(-235,75),     S(-346,143),    S(-456,123),    S(-87,104),     S(-23,71),      //
    S(-25,-40),     S(-54,97),      S(29,36),       S(33,11),       S(-42,72),      S(-22,59),      S(-22,40),      S(-135,47),     //
    S(46,45),       S(75,58),       S(260,40),      S(121,47),      S(79,61),       S(-4,96),       S(94,21),       S(7,35),        //
    S(69,-36),      S(10,61),       S(128,23),      S(118,62),      S(157,38),      S(50,66),       S(16,48),       S(-104,96),     //
    S(20,-39),      S(19,27),       S(27,39),       S(89,58),       S(65,91),       S(14,56),       S(-15,22),      S(-38,-45),     //
    S(54,-21),      S(65,-11),      S(94,-17),      S(18,52),       S(2,68),        S(-19,78),      S(33,-15),      S(11,-47),      //
    S(-4,-59),      S(85,-43),      S(65,-42),      S(18,-7),       S(-4,-11),      S(22,-10),      S(-23,7),       S(49,-153),     //
    S(-57,58),      S(-72,36),      S(-76,43),      S(-29,-36),     S(-65,-33),     S(-37,-7),      S(-9,-59),      S(-63,9),       //
};
const std::array<PScore, 64> ROOK_PSQT = {
    S(217,-19),     S(376,-29),     S(78,56),       S(89,55),       S(140,20),      S(23,62),       S(80,53),       S(62,61),       //
    S(265,-4),      S(212,47),      S(369,-8),      S(211,75),      S(211,72),      S(98,103),      S(62,97),       S(82,87),       //
    S(101,44),      S(337,-24),     S(269,0),       S(227,16),      S(143,31),      S(56,96),       S(72,59),       S(-25,83),      //
    S(12,47),       S(58,33),       S(79,38),       S(114,-4),      S(56,21),       S(-17,115),     S(-22,72),      S(-124,92),     //
    S(-97,-39),     S(41,-53),      S(-36,29),      S(-40,23),      S(-80,36),      S(-120,90),     S(-158,80),     S(-170,58),     //
    S(-117,-56),    S(38,-130),     S(-46,-43),     S(-74,-18),     S(-69,-34),     S(-144,39),     S(-164,17),     S(-184,14),     //
    S(-165,0),      S(-54,-96),     S(-54,-72),     S(-62,-42),     S(-64,-39),     S(-111,-6),     S(-160,-28),    S(-192,-37),    //
    S(-152,-19),    S(-105,11),     S(-74,-19),     S(-36,-35),     S(-72,-6),      S(-82,-12),     S(-101,-34),    S(-133,-28),    //
};
const std::array<PScore, 64> QUEEN_PSQT = {
    S(99,53),       S(118,12),      S(134,138),     S(138,112),     S(120,91),      S(-46,220),     S(21,80),       S(-76,63),      //
    S(105,111),     S(-105,298),    S(88,247),      S(-93,406),     S(-70,306),     S(-147,303),    S(-111,165),    S(-54,76),      //
    S(125,152),     S(207,121),     S(230,193),     S(99,245),      S(-31,289),     S(-56,224),     S(-19,90),      S(4,-22),       //
    S(54,134),      S(34,198),      S(18,205),      S(-13,283),     S(-33,227),     S(-17,100),     S(-34,49),      S(-61,51),      //
    S(-20,117),     S(43,76),       S(-26,206),     S(-21,162),     S(-65,176),     S(-70,110),     S(-33,-49),     S(-76,-43),     //
    S(3,-97),       S(17,-13),      S(8,47),        S(-44,59),      S(-27,-12),     S(-30,-51),     S(-36,-74),     S(-74,-23),     //
    S(-1,-217),     S(11,-293),     S(-9,-144),     S(31,-133),     S(-19,-94),     S(-2,-175),     S(-34,-119),    S(-105,-13),    //
    S(-192,-19),    S(-76,-398),    S(-73,-240),    S(-28,-244),    S(-9,-156),     S(9,-237),      S(-62,-105),    S(-117,-8),     //
};
const std::array<PScore, 64> KING_PSQT = {
    S(504,-616),    S(373,-180),    S(-503,149),    S(-581,153),    S(0,0),         S(0,0),         S(0,0),         S(0,0),         //
    S(187,-84),     S(-196,199),    S(-195,227),    S(-115,204),    S(0,0),         S(0,0),         S(0,0),         S(0,0),         //
    S(-187,68),     S(-72,158),     S(18,135),      S(-103,120),    S(0,0),         S(0,0),         S(0,0),         S(0,0),         //
    S(-353,72),     S(-211,176),    S(-92,136),     S(-184,118),    S(0,0),         S(0,0),         S(0,0),         S(0,0),         //
    S(-275,-1),     S(-209,102),    S(-156,102),    S(-329,166),    S(0,0),         S(0,0),         S(0,0),         S(0,0),         //
    S(-180,-56),    S(-37,-3),      S(-195,73),     S(-318,150),    S(0,0),         S(0,0),         S(0,0),         S(0,0),         //
    S(118,-153),    S(145,-81),     S(-13,-2),      S(-141,62),     S(0,0),         S(0,0),         S(0,0),         S(0,0),         //
    S(128,-285),    S(168,-213),    S(-16,-148),    S(7,-200),      S(0,0),         S(0,0),         S(0,0),         S(0,0),         //
};
// clang-format on

Score evaluate_white_pov(const Position& pos, const PsqtState& psqt_state) {

    const Color us    = pos.active_color();
    i32         phase = pos.piece_count(Color::White, PieceType::Knight)
              + pos.piece_count(Color::Black, PieceType::Knight)
              + pos.piece_count(Color::White, PieceType::Bishop)
              + pos.piece_count(Color::Black, PieceType::Bishop)
              + 2
                  * (pos.piece_count(Color::White, PieceType::Rook)
                     + pos.piece_count(Color::Black, PieceType::Rook))
              + 4
                  * (pos.piece_count(Color::White, PieceType::Queen)
                     + pos.piece_count(Color::Black, PieceType::Queen));

    phase = std::min<i32>(phase, 24);

    PScore mobility = PSCORE_ZERO;

    auto add_mobility = [&](Color c, PScore& mob_count) {
        Bitboard bb = pos.board().get_color_bitboard(c) | pos.attacked_by(~c, PieceType::Pawn);
        for (PieceId id : pos.get_piece_mask(c, PieceType::Knight)) {
            mobility += KNIGHT_MOBILITY[pos.mobility_of(c, id, ~bb)];
        }
        for (PieceId id : pos.get_piece_mask(c, PieceType::Bishop)) {
            mobility += BISHOP_MOBILITY[pos.mobility_of(c, id, ~bb)];
        }
        for (PieceId id : pos.get_piece_mask(c, PieceType::Rook)) {
            mobility += ROOK_MOBILITY[pos.mobility_of(c, id, ~bb)];
        }
        for (PieceId id : pos.get_piece_mask(c, PieceType::Queen)) {
            mobility += QUEEN_MOBILITY[pos.mobility_of(c, id, ~bb)];
        }
        mobility += KING_MOBILITY[pos.mobility_of(c, PieceId::king(), ~bb)];
    };

    add_mobility(Color::Black, mobility);
    mobility *= -1;  // Persy trick
    add_mobility(Color::White, mobility);


    const std::array<Bitboard, 2> pawns = {pos.board().bitboard_for(Color::White, PieceType::Pawn),
                                           pos.board().bitboard_for(Color::Black, PieceType::Pawn)};

    PScore doubled_pawns_bonus = DOUBLED_PAWN_VAL
                               * ((pawns[0] & pawns[0].shift(Direction::North)).popcount()
                                  - (pawns[1] & pawns[1].shift(Direction::South)).popcount());

    PScore bishop_pair_bonus = BISHOP_PAIR_VAL
                             * ((pos.piece_count(Color::White, PieceType::Bishop) >= 2)
                                - (pos.piece_count(Color::Black, PieceType::Bishop) >= 2));

    i32 rfb_count = 0;
    for (PieceId rookId : pos.get_piece_mask(Color::White, PieceType::Rook)) {
        Square   sq = pos.piece_list_sq(Color::White)[rookId];
        Bitboard bb =
          pos.attack_table(Color::White).get_piece_mask_bitboard(rookId.to_piece_mask());
        rfb_count += (bb & (Bitboard(-1) << (sq.raw + 7))).popcount();
    }
    for (PieceId rookId : pos.get_piece_mask(Color::Black, PieceType::Rook)) {
        Square   sq = pos.piece_list_sq(Color::Black)[rookId];
        Bitboard bb =
          pos.attack_table(Color::Black).get_piece_mask_bitboard(rookId.to_piece_mask());
        rfb_count -= (bb & (Bitboard(-1) >> (70 - sq.raw))).popcount();
    }

    PScore rfb = RFB_VAL * rfb_count;

    PScore tempo = (us == Color::White) ? TEMPO_VAL : -TEMPO_VAL;
    PScore sum =
      psqt_state.score() + mobility + tempo + bishop_pair_bonus + doubled_pawns_bonus + rfb;
    return sum->phase<24>(phase);
};

Score evaluate_stm_pov(const Position& pos, const PsqtState& psqt_state) {
    const Color us = pos.active_color();
    return (us == Color::White) ? evaluate_white_pov(pos, psqt_state)
                                : -evaluate_white_pov(pos, psqt_state);
}

}  // namespace Clockwork
