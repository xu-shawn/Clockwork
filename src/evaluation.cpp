#include <array>
#include <ranges>

#include "bitboard.hpp"
#include "common.hpp"
#include "eval_constants.hpp"
#include "position.hpp"
#include "psqt_state.hpp"

#include "evaluation.hpp"

#include "eval_types.hpp"
#include "square.hpp"

namespace Clockwork {

// clang-format off
const PScore PAWN_MAT   = S(281, 536);
const PScore KNIGHT_MAT = S(849, 1002);
const PScore BISHOP_MAT = S(869, 1096);
const PScore ROOK_MAT   = S(1294, 1796);
const PScore QUEEN_MAT  = S(2797, 3284);
const PScore TEMPO_VAL  = S(28, 15);

const PScore BISHOP_PAIR_VAL  = S(53, 216);
const PScore DOUBLED_PAWN_VAL = S(-72, -117);

const std::array<PScore, 9> KNIGHT_MOBILITY = {
    S(-217, -260), S(-136, -128), S(-82, -38), S(-42, -1), S(2, 17), S(26, 63), S(54, 65), S(88, 57), S(134, -17),
};
const std::array<PScore, 14> BISHOP_MOBILITY = {
    S(-192, -284), S(-135, -184), S(-73, -141), S(-51, -80), S(-11, -42), S(6, -16), S(33, -15), S(43, -2), S(50, 14), S(47, 12), S(75, 2), S(166, -65), S(195, -103), S(290, -162),
};
const std::array<PScore, 15> ROOK_MOBILITY = {
    S(-277, -359), S(-110, -106), S(-69, -46), S(-55, -31), S(-39, -8), S(-26, -1), S(-7, 17), S(23, 11), S(55, 12), S(77, 32), S(105, 24), S(117, 34), S(174, 19), S(138, 33), S(261, -78),
};
const std::array<PScore, 28> QUEEN_MOBILITY = {
    S(-112, 11), S(-278, -73), S(-204, -470), S(-179, -252), S(-131, -320), S(-113, -242), S(-143, -42), S(-112, -69), S(-94, -45), S(-79, -27), S(-84, 24), S(-75, 52), S(-44, 38), S(-41, 50), S(-21, 47), S(-26, 66), S(-31, 98), S(-12, 66), S(-1, 51), S(48, -12), S(83, -50), S(150, -125), S(132, -104), S(452, -419), S(402, -401), S(1023, -703), S(623, -430), S(1446, -1049),
};
const std::array<PScore, 9> KING_MOBILITY = {
    S(458, 725), S(191, 383), S(63, 435), S(43, 470), S(2, 466), S(-42, 460), S(-83, 502), S(-97, 494), S(-17, 382),
};

const std::array<PScore, 3> PAWN_KING_RING = {
    CS(0, 0), S(50, -40), S(101, -79),
};
const std::array<PScore, 3> KNIGHT_KING_RING = {
    CS(0, 0), S(90, -43), S(123, -88),
};
const std::array<PScore, 3> BISHOP_KING_RING = {
    CS(0, 0), S(66, -10), S(146, -51),
};
const std::array<PScore, 5> ROOK_KING_RING = {
    CS(0, 0), S(80, -60), S(176, -94), S(230, -92), S(312, -137),
};
const std::array<PScore, 6> QUEEN_KING_RING = {
    CS(0, 0), S(5, 47), S(97, 29), S(270, -40), S(554, -120), S(809, -247),
};

const std::array<PScore, 48> PAWN_PSQT = {
    S(-178, 446),   S(17, 415),     S(103, 441),    S(243, 219),    S(190, 227),    S(252, 312),    S(100, 344),    S(188, 317),    //
    S(-51, 111),    S(106, 174),    S(66, 69),      S(165, 0),      S(101, 0),      S(8, 52),       S(-47, 95),     S(-100, 53),    //
    S(-71, -59),    S(-39, -48),    S(-44, -96),    S(-37, -140),   S(-47, -122),   S(-92, -127),   S(-124, -59),   S(-157, -42),   //
    S(-54, -166),   S(1, -128),     S(-44, -168),   S(-60, -161),   S(-58, -187),   S(-103, -172),  S(-146, -94),   S(-180, -111),  //
    S(-16, -203),   S(87, -193),    S(-9, -158),    S(-58, -143),   S(-77, -151),   S(-125, -158),  S(-130, -119),  S(-179, -133),  //
    S(-72, -197),   S(128, -203),   S(28, -164),    S(-77, -105),   S(-93, -156),   S(-130, -149),  S(-137, -104),  S(-181, -127),  //
};
const std::array<PScore, 64> KNIGHT_PSQT = {
    S(-333, -161),  S(1, -123),     S(-533, 265),   S(12, 56),      S(-246, 140),   S(-286, 157),   S(-254, -37),   S(-410, -6),    //
    S(62, -64),     S(56, 81),      S(215, -33),    S(64, 54),      S(148, 58),     S(132, -53),    S(-8, -19),     S(66, -83),     //
    S(22, 51),      S(62, 126),     S(230, 99),     S(145, 77),     S(129, 85),     S(61, 66),      S(9, 76),       S(-90, 36),     //
    S(112, 26),     S(10, 111),     S(116, 97),     S(43, 119),     S(125, 86),     S(51, 83),      S(-22, 39),     S(-13, 54),     //
    S(49, 32),      S(146, 30),     S(61, 64),      S(55, 67),      S(19, 89),      S(18, 75),      S(-23, 59),     S(-21, -42),    //
    S(-44, -4),     S(-8, -24),     S(-35, -14),    S(2, 51),       S(7, 42),       S(-89, 13),     S(-71, -17),    S(-101, -21),   //
    S(-2, 30),      S(9, 18),       S(-47, -2),     S(-47, 12),     S(-51, -12),    S(-107, -8),    S(-88, -28),    S(-140, -106),  //
    S(-124, 8),     S(-29, -53),    S(4, -78),      S(22, -37),     S(5, -43),      S(-44, -128),   S(-90, -17),    S(-235, 0),     //
};
const std::array<PScore, 64> BISHOP_PSQT = {
    S(-136, 64),    S(-65, 13),     S(-575, 118),   S(-281, 88),    S(-343, 136),   S(-448, 112),   S(-48, 87),     S(11, 66),      //
    S(-55, -15),    S(-46, 87),     S(17, 35),      S(13, 7),       S(-8, 53),      S(-5, 43),      S(4, 22),       S(-114, 38),    //
    S(-28, 84),     S(31, 70),      S(214, 46),     S(80, 52),      S(43, 60),      S(-3, 81),      S(95, 14),      S(-7, 46),      //
    S(38, -24),     S(16, 51),      S(95, 24),      S(72, 68),      S(121, 37),     S(26, 57),      S(22, 37),      S(-96, 89),     //
    S(37, -47),     S(22, 18),      S(33, 25),      S(58, 60),      S(36, 88),      S(7, 42),       S(-19, 11),     S(-18, -50),    //
    S(60, -21),     S(84, -15),     S(86, -15),     S(16, 47),      S(-1, 59),      S(-27, 68),     S(49, -22),     S(18, -49),     //
    S(-10, -43),    S(109, -48),    S(58, -38),     S(3, 6),        S(-11, -13),    S(24, -17),     S(-18, -5),     S(50, -133),    //
    S(7, 51),       S(-13, 21),     S(-15, 34),     S(9, -50),      S(-32, -44),    S(9, -6),       S(4, -56),      S(-44, 11),     //
};
const std::array<PScore, 64> ROOK_PSQT = {
    S(114, 8),      S(303, -14),    S(13, 82),      S(28, 83),      S(88, 45),      S(0, 76),       S(66, 51),      S(63, 59),      //
    S(158, 29),     S(127, 68),     S(241, 30),     S(95, 114),     S(117, 97),     S(13, 126),     S(-18, 118),    S(18, 104),     //
    S(33, 67),      S(262, 3),      S(205, 27),     S(201, 21),     S(124, 34),     S(37, 98),      S(62, 62),      S(-40, 87),     //
    S(-19, 64),     S(17, 56),      S(38, 63),      S(111, -2),     S(58, 18),      S(-11, 112),    S(-15, 71),     S(-111, 88),    //
    S(-109, -23),   S(26, -37),     S(-68, 54),     S(-44, 25),     S(-73, 29),     S(-104, 83),    S(-136, 72),    S(-149, 53),    //
    S(-119, -45),   S(22, -111),    S(-67, -22),    S(-81, -11),    S(-61, -39),    S(-136, 35),    S(-145, 11),    S(-167, 12),    //
    S(-150, 2),     S(-51, -93),    S(-38, -70),    S(-52, -45),    S(-57, -43),    S(-96, -15),    S(-148, -32),   S(-168, -40),   //
    S(-127, -29),   S(-87, -1),     S(-58, -34),    S(-32, -44),    S(-59, -19),    S(-69, -29),    S(-88, -44),    S(-117, -36),   //
};
const std::array<PScore, 64> QUEEN_PSQT = {
    S(52, 3),       S(55, -10),     S(-2, 156),     S(-32, 135),    S(-44, 133),    S(-98, 210),    S(-18, 74),     S(-60, 12),     //
    S(85, 70),      S(-138, 296),   S(-3, 263),     S(-194, 416),   S(-88, 272),    S(-168, 300),   S(-106, 148),   S(-37, 66),     //
    S(-62, 219),    S(75, 175),     S(79, 234),     S(39, 242),     S(-60, 291),    S(-60, 230),    S(-14, 102),    S(-20, 29),     //
    S(43, 81),      S(45, 143),     S(6, 165),      S(-28, 271),    S(-37, 242),    S(-2, 99),      S(-1, 49),      S(-32, 59),     //
    S(16, 82),      S(75, 38),      S(-13, 190),    S(-14, 165),    S(-57, 184),    S(-42, 112),    S(5, -56),      S(-32, -28),    //
    S(51, -130),    S(47, -30),     S(23, 43),      S(-42, 92),     S(-11, 7),      S(-14, -26),    S(0, -68),      S(-23, -33),    //
    S(39, -245),    S(56, -314),    S(18, -147),    S(36, -97),     S(-15, -49),    S(24, -162),    S(-9, -101),    S(-58, -26),    //
    S(-133, -39),   S(-4, -447),    S(-28, -265),   S(-5, -225),    S(26, -154),    S(41, -231),    S(-19, -124),   S(-84, -23),    //
};
const std::array<PScore, 64> KING_PSQT = {
    S(457, -556),   S(414, -149),   S(-505, 191),   S(-529, 185),   S(0, 0),        S(0, 0),        S(0, 0),        S(0, 0),        //
    S(188, -37),    S(-117, 169),   S(-102, 197),   S(-2, 175),     S(0, 0),        S(0, 0),        S(0, 0),        S(0, 0),        //
    S(-166, 98),    S(46, 120),     S(94, 104),     S(2, 82),       S(0, 0),        S(0, 0),        S(0, 0),        S(0, 0),        //
    S(-307, 96),    S(-89, 131),    S(66, 86),      S(-32, 70),     S(0, 0),        S(0, 0),        S(0, 0),        S(0, 0),        //
    S(-271, 26),    S(-55, 51),     S(31, 37),      S(-145, 102),   S(0, 0),        S(0, 0),        S(0, 0),        S(0, 0),        //
    S(-191, -22),   S(78, -39),     S(-24, 14),     S(-112, 79),    S(0, 0),        S(0, 0),        S(0, 0),        S(0, 0),        //
    S(75, -100),    S(188, -86),    S(69, -25),     S(-55, 37),     S(0, 0),        S(0, 0),        S(0, 0),        S(0, 0),        //
    S(-16, -182),   S(97, -138),    S(-40, -91),    S(-5, -130),    S(0, 0),        S(0, 0),        S(0, 0),        S(0, 0),        //
};
// clang-format on

std::array<Bitboard, 64> king_ring_table = []() {
    std::array<Bitboard, 64> king_ring_table{};
    for (u8 sq_idx = 0; sq_idx < 64; sq_idx++) {
        Bitboard sq_bb     = Bitboard::from_square(Square{sq_idx});
        Bitboard king_ring = sq_bb;
        king_ring |= sq_bb.shift(Direction::North);
        king_ring |= sq_bb.shift(Direction::South);
        king_ring |= sq_bb.shift(Direction::East);
        king_ring |= sq_bb.shift(Direction::West);
        king_ring |= sq_bb.shift(Direction::NorthEast);
        king_ring |= sq_bb.shift(Direction::SouthEast);
        king_ring |= sq_bb.shift(Direction::NorthWest);
        king_ring |= sq_bb.shift(Direction::SouthWest);
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
        for (PieceId id : pos.get_piece_mask(c, PieceType::Pawn)) {
            k_attack += PAWN_KING_RING[pos.mobility_of(c, id, king_ring)];
        }
        for (PieceId id : pos.get_piece_mask(c, PieceType::Knight)) {
            mobility += KNIGHT_MOBILITY[pos.mobility_of(c, id, ~bb)];
            k_attack += KNIGHT_KING_RING[pos.mobility_of(c, id, king_ring)];
        }
        for (PieceId id : pos.get_piece_mask(c, PieceType::Bishop)) {
            mobility += BISHOP_MOBILITY[pos.mobility_of(c, id, ~bb)];
            k_attack += BISHOP_KING_RING[pos.mobility_of(c, id, king_ring)];
        }
        for (PieceId id : pos.get_piece_mask(c, PieceType::Rook)) {
            mobility += ROOK_MOBILITY[pos.mobility_of(c, id, ~bb)];
            k_attack += ROOK_KING_RING[pos.mobility_of(c, id, king_ring)];
        }
        for (PieceId id : pos.get_piece_mask(c, PieceType::Queen)) {
            mobility += QUEEN_MOBILITY[pos.mobility_of(c, id, ~bb)];
            k_attack += QUEEN_KING_RING[pos.mobility_of(c, id, king_ring)];
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
