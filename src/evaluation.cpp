#include <array>
#include <ranges>

#include "bitboard.hpp"
#include "common.hpp"
#include "position.hpp"
#include "psqt_state.hpp"

#include "evaluation.hpp"

#include "eval_types.hpp"
#include "square.hpp"

namespace Clockwork {

// clang-format off
const PScore PAWN_MAT   = S(292,529);
const PScore KNIGHT_MAT = S(823,1020);
const PScore BISHOP_MAT = S(859,1111);
const PScore ROOK_MAT   = S(1245,1805);
const PScore QUEEN_MAT  = S(2788,3193);
const PScore TEMPO_VAL  = S(30,14);

const PScore BISHOP_PAIR_VAL  = S(51,219);
const PScore DOUBLED_PAWN_VAL = S(-72,-116);

const std::array<PScore, 9> KNIGHT_MOBILITY = {
    S(-234,-265), S(-150,-135), S(-96,-43), S(-56,-4), S(-7,13), S(16,59), S(45,63), S(81,52), S(131,-23),
};
const std::array<PScore, 14> BISHOP_MOBILITY = {
    S(-199,-290), S(-135,-199), S(-82,-148), S(-64,-86), S(-26,-46), S(-9,-19), S(15,-17), S(25,-5), S(35,11), S(34,6), S(65,-4), S(164,-77), S(188,-113), S(301,-174),
};
const std::array<PScore, 15> ROOK_MOBILITY = {
    S(-260,-362), S(-95,-103), S(-57,-42), S(-43,-27), S(-29,-3), S(-15,2), S(0,23), S(26,18), S(56,20), S(72,44), S(91,39), S(95,52), S(149,38), S(114,55), S(243,-54),
};
const std::array<PScore, 28> QUEEN_MOBILITY = {
    S(-149,-8), S(-189,-266), S(-171,-491), S(-160,-251), S(-111,-340), S(-100,-258), S(-133,-59), S(-106,-79), S(-92,-54), S(-81,-35), S(-91,23), S(-83,48), S(-56,34), S(-57,47), S(-38,41), S(-44,60), S(-52,89), S(-29,50), S(-16,33), S(22,-25), S(69,-72), S(130,-149), S(132,-141), S(446,-459), S(427,-464), S(929,-696), S(515,-414), S(1105,-922),
};
const std::array<PScore, 9> KING_MOBILITY = {
    S(487,725), S(173,418), S(50,461), S(31,489), S(-10,478), S(-50,455), S(-64,470), S(-73,445), S(7,318),
};

const PScore KNIGHT_KING_RING = S(38,-21);
const PScore BISHOP_KING_RING = S(27,-8);
const PScore ROOK_KING_RING   = S(40,-16);
const PScore QUEEN_KING_RING  = S(29,17);

const std::array<PScore, 48> PAWN_PSQT = {
    S(-163,443),    S(43,408),      S(123,430),     S(235,216),     S(182,229),     S(245,315),     S(118,339),     S(186,325),     //
    S(-39,102),     S(137,155),     S(80,54),       S(186,-15),     S(117,-10),     S(17,47),       S(-38,92),      S(-97,52),      //
    S(-76,-61),     S(-34,-56),     S(-54,-99),     S(-43,-141),    S(-43,-125),    S(-92,-127),    S(-121,-60),    S(-162,-38),    //
    S(-63,-165),    S(-8,-128),     S(-39,-177),    S(-64,-166),    S(-67,-187),    S(-107,-170),   S(-148,-92),    S(-185,-108),   //
    S(-20,-205),    S(86,-198),     S(-6,-165),     S(-64,-147),    S(-92,-148),    S(-140,-152),   S(-139,-114),   S(-189,-127),   //
    S(-78,-200),    S(126,-210),    S(26,-169),     S(-90,-102),    S(-102,-156),   S(-146,-141),   S(-147,-99),    S(-191,-121),   //
};
const std::array<PScore, 64> KNIGHT_PSQT = {
    S(-320,-147),   S(16,-127),     S(-535,261),    S(30,58),       S(-238,137),    S(-253,151),    S(-244,-42),    S(-367,-22),    //
    S(41,-50),      S(40,89),       S(195,-28),     S(84,40),       S(164,48),      S(115,-44),     S(3,-23),       S(82,-84),      //
    S(41,44),       S(69,121),      S(193,114),     S(137,77),      S(124,90),      S(45,77),       S(2,81),        S(-67,28),      //
    S(136,19),      S(32,93),       S(92,109),      S(32,128),      S(101,103),     S(15,105),      S(-9,31),       S(3,49),        //
    S(28,56),       S(120,44),      S(27,86),       S(12,94),       S(-31,121),     S(10,83),       S(-13,52),      S(-1,-46),      //
    S(-42,2),       S(-11,-14),     S(-44,-3),      S(-7,62),       S(13,41),       S(-88,14),      S(-60,-21),     S(-84,-21),     //
    S(33,17),       S(47,10),       S(-25,-4),      S(-25,8),       S(-28,-21),     S(-87,-15),     S(-65,-33),     S(-113,-119),   //
    S(-108,15),     S(-7,-58),      S(35,-86),      S(41,-38),      S(24,-47),      S(-26,-135),    S(-65,-25),     S(-206,-9),     //
};
const std::array<PScore, 64> BISHOP_PSQT = {
    S(-175,69),     S(-106,16),     S(-551,107),    S(-269,82),     S(-378,141),    S(-469,115),    S(-56,85),      S(10,62),       //
    S(-51,-19),     S(-57,85),      S(10,32),       S(-3,7),        S(-55,65),      S(-13,44),      S(6,19),        S(-113,37),     //
    S(10,62),       S(51,60),       S(212,44),      S(92,42),       S(61,52),       S(-18,83),      S(103,7),       S(11,34),       //
    S(41,-26),      S(-17,65),      S(77,29),       S(83,64),       S(137,31),      S(34,53),       S(10,37),       S(-94,87),      //
    S(-3,-29),      S(-19,36),      S(0,39),        S(50,62),       S(34,89),       S(8,40),        S(-19,11),      S(-30,-52),     //
    S(27,-5),       S(82,-12),      S(98,-23),      S(0,49),        S(-11,59),      S(-27,66),      S(52,-24),      S(19,-52),      //
    S(-7,-47),      S(120,-49),     S(72,-39),      S(12,0),        S(-18,-13),     S(16,-15),      S(-14,-8),      S(55,-137),     //
    S(-13,66),      S(-11,20),      S(-11,37),      S(9,-47),       S(-24,-53),     S(-4,-2),       S(-5,-51),      S(-41,9),       //
};
const std::array<PScore, 64> ROOK_PSQT = {
    S(110,14),      S(313,-13),     S(7,89),        S(4,96),        S(82,50),       S(20,71),       S(93,45),       S(76,59),       //
    S(161,29),      S(102,79),      S(214,39),      S(74,119),      S(113,95),      S(12,123),      S(-12,112),     S(29,98),       //
    S(23,69),       S(220,18),      S(133,54),      S(107,56),      S(39,67),       S(5,109),       S(43,68),       S(-43,86),      //
    S(-58,78),      S(-16,70),      S(-4,77),       S(16,37),       S(4,38),        S(-22,114),     S(-30,76),      S(-122,92),     //
    S(-106,-25),    S(14,-32),      S(-79,58),      S(-58,29),      S(-86,36),      S(-101,80),     S(-135,74),     S(-139,50),     //
    S(-97,-56),     S(23,-109),     S(-64,-20),     S(-79,-13),     S(-61,-36),     S(-132,35),     S(-139,11),     S(-152,9),      //
    S(-109,-16),    S(-26,-95),     S(-21,-73),     S(-47,-43),     S(-49,-44),     S(-82,-18),     S(-134,-35),    S(-144,-47),    //
    S(-113,-31),    S(-70,-9),      S(-41,-36),     S(-25,-45),     S(-49,-22),     S(-53,-31),     S(-70,-49),     S(-96,-39),     //
};
const std::array<PScore, 64> QUEEN_PSQT = {
    S(107,-12),     S(92,-47),      S(68,82),       S(34,64),       S(21,56),       S(-92,161),     S(41,15),       S(-19,-1),      //
    S(92,68),       S(-146,295),    S(-26,227),     S(-233,379),    S(-158,270),    S(-170,269),    S(-105,158),    S(-31,77),      //
    S(63,121),      S(93,110),      S(74,174),      S(-40,220),     S(-131,262),    S(-103,212),    S(-9,80),       S(16,8),        //
    S(-5,88),       S(-38,145),     S(-82,165),     S(-117,245),    S(-90,212),     S(-27,76),      S(-34,42),      S(-44,71),      //
    S(-30,59),      S(-7,47),       S(-76,185),     S(-60,148),     S(-71,173),     S(-61,127),     S(-12,-42),     S(-42,-35),     //
    S(19,-118),     S(25,-5),       S(12,62),       S(-50,66),      S(-20,9),       S(-9,1),        S(2,-44),       S(-30,-14),     //
    S(51,-228),     S(76,-285),     S(39,-123),     S(58,-100),     S(-3,-53),      S(26,-138),     S(2,-75),       S(-52,2),       //
    S(-94,-21),     S(7,-389),      S(-5,-246),     S(17,-227),     S(51,-144),     S(47,-218),     S(-21,-93),     S(-73,18),      //
};
const std::array<PScore, 64> KING_PSQT = {
    S(418,-605),    S(300,-154),    S(-555,173),    S(-522,161),    S(0,0),         S(0,0),         S(0,0),         S(0,0),         //
    S(163,-69),     S(-166,204),    S(-98,220),     S(64,186),      S(0,0),         S(0,0),         S(0,0),         S(0,0),         //
    S(-129,61),     S(75,138),      S(170,115),     S(99,86),       S(0,0),         S(0,0),         S(0,0),         S(0,0),         //
    S(-270,62),     S(-56,149),     S(138,96),      S(81,72),       S(0,0),         S(0,0),         S(0,0),         S(0,0),         //
    S(-234,-3),     S(-27,68),      S(108,46),      S(-35,101),     S(0,0),         S(0,0),         S(0,0),         S(0,0),         //
    S(-176,-45),    S(80,-20),      S(23,25),       S(-33,83),      S(0,0),         S(0,0),         S(0,0),         S(0,0),         //
    S(36,-108),     S(152,-57),     S(95,-11),      S(-8,48),       S(0,0),         S(0,0),         S(0,0),         S(0,0),         //
    S(-68,-202),    S(62,-145),     S(-32,-110),    S(-4,-138),     S(0,0),         S(0,0),         S(0,0),         S(0,0),         //
};
// clang-format on

std::array<Bitboard, 64> king_ring_table = []() {
    std::array<Bitboard, 64> king_ring_table{};
    for (u8 sq_idx = 0; sq_idx < 64; sq_idx++) {
        Bitboard sq_bb = Bitboard::from_square(Square{sq_idx});
        Bitboard king_ring{};
        king_ring |= king_ring.shift(Direction::North);
        king_ring |= king_ring.shift(Direction::South);
        king_ring |= king_ring.shift(Direction::East);
        king_ring |= king_ring.shift(Direction::West);
        king_ring |= king_ring.shift(Direction::NorthEast);
        king_ring |= king_ring.shift(Direction::SouthEast);
        king_ring |= king_ring.shift(Direction::NorthWest);
        king_ring |= king_ring.shift(Direction::SouthWest);
        king_ring_table[sq_idx] = king_ring;
    }
    return king_ring_table;
}();

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

    PScore mobility    = PSCORE_ZERO;
    PScore king_attack = PSCORE_ZERO;

    auto add_mobility = [&](Color c, PScore& mob_count, PScore& k_attack) {
        Bitboard bb = pos.bitboard_for(c, PieceType::Pawn) | pos.attacked_by(~c, PieceType::Pawn);
        Bitboard king_ring = king_ring_table[pos.king_sq(~c).raw];
        for (PieceId id : pos.get_piece_mask(c, PieceType::Knight)) {
            mobility += KNIGHT_MOBILITY[pos.mobility_of(c, id, ~bb)];
            k_attack += KNIGHT_KING_RING * pos.mobility_of(c, id, king_ring);
        }
        for (PieceId id : pos.get_piece_mask(c, PieceType::Bishop)) {
            mobility += BISHOP_MOBILITY[pos.mobility_of(c, id, ~bb)];
            k_attack += BISHOP_KING_RING * pos.mobility_of(c, id, king_ring);
        }
        for (PieceId id : pos.get_piece_mask(c, PieceType::Rook)) {
            mobility += ROOK_MOBILITY[pos.mobility_of(c, id, ~bb)];
            k_attack += ROOK_KING_RING * pos.mobility_of(c, id, king_ring);
        }
        for (PieceId id : pos.get_piece_mask(c, PieceType::Queen)) {
            mobility += QUEEN_MOBILITY[pos.mobility_of(c, id, ~bb)];
            k_attack += QUEEN_KING_RING * pos.mobility_of(c, id, king_ring);
        }
        mobility += KING_MOBILITY[pos.mobility_of(c, PieceId::king(), ~bb)];
    };

    add_mobility(Color::Black, mobility, king_attack);
    mobility *= -1;  // Persy trick
    king_attack *= -1;
    add_mobility(Color::White, mobility, king_attack);

    const std::array<Bitboard, 2> pawns = {pos.board().bitboard_for(Color::White, PieceType::Pawn),
                                           pos.board().bitboard_for(Color::Black, PieceType::Pawn)};

    PScore doubled_pawns_bonus = DOUBLED_PAWN_VAL
                               * ((pawns[0] & pawns[0].shift(Direction::North)).popcount()
                                  - (pawns[1] & pawns[1].shift(Direction::South)).popcount());

    PScore bishop_pair_bonus = BISHOP_PAIR_VAL
                             * ((pos.piece_count(Color::White, PieceType::Bishop) >= 2)
                                - (pos.piece_count(Color::Black, PieceType::Bishop) >= 2));

    PScore tempo = (us == Color::White) ? TEMPO_VAL : -TEMPO_VAL;
    PScore sum =
      psqt_state.score() + mobility + king_attack + tempo + bishop_pair_bonus + doubled_pawns_bonus;
    return sum->phase<24>(phase);
};

Score evaluate_stm_pov(const Position& pos, const PsqtState& psqt_state) {
    const Color us = pos.active_color();
    return (us == Color::White) ? evaluate_white_pov(pos, psqt_state)
                                : -evaluate_white_pov(pos, psqt_state);
}

}  // namespace Clockwork
