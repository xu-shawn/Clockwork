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
const PScore PAWN_MAT   = S(290,530);
const PScore KNIGHT_MAT = S(841,1007);
const PScore BISHOP_MAT = S(863,1108);
const PScore ROOK_MAT   = S(1273,1799);
const PScore QUEEN_MAT  = S(2787,3279);
const PScore TEMPO_VAL  = S(29,15);

const PScore BISHOP_PAIR_VAL  = S(53,217);
const PScore DOUBLED_PAWN_VAL = S(-72,-118);

const std::array<PScore, 9> KNIGHT_MOBILITY = {
    S(-221,-269), S(-140,-132), S(-86,-42), S(-47,-2), S(-1,16), S(21,62), S(49,65), S(84,56), S(130,-18),
};
const std::array<PScore, 14> BISHOP_MOBILITY = {
    S(-195,-287), S(-139,-187), S(-77,-143), S(-56,-82), S(-16,-44), S(1,-17), S(28,-15), S(38,-3), S(46,13), S(44,10), S(72,1), S(163,-68), S(192,-107), S(295,-169),
};
const std::array<PScore, 15> ROOK_MOBILITY = {
    S(-268,-354), S(-106,-106), S(-66,-44), S(-52,-28), S(-35,-7), S(-21,0), S(-2,18), S(27,12), S(60,12), S(82,33), S(109,25), S(123,35), S(180,20), S(143,37), S(268,-72),
};
const std::array<PScore, 28> QUEEN_MOBILITY = {
    S(-159,-13), S(-209,-281), S(-182,-529), S(-170,-271), S(-125,-341), S(-110,-258), S(-142,-54), S(-113,-77), S(-97,-52), S(-83,-34), S(-90,20), S(-82,50), S(-52,37), S(-52,51), S(-33,48), S(-39,70), S(-47,103), S(-23,67), S(-11,53), S(34,-9), S(76,-54), S(136,-122), S(132,-113), S(442,-420), S(407,-415), S(959,-677), S(534,-375), S(1103,-876),
};
const std::array<PScore, 9> KING_MOBILITY = {
    S(436,721), S(155,431), S(38,473), S(25,501), S(-9,489), S(-42,464), S(-53,478), S(-52,450), S(34,321),
};

const PScore KNIGHT_KING_RING = S(67,-46);
const PScore BISHOP_KING_RING = S(72,-24);
const PScore ROOK_KING_RING   = S(77,-32);
const PScore QUEEN_KING_RING  = S(69,16);

const std::array<PScore, 48> PAWN_PSQT = {
    S(-176,446),    S(35,407),      S(115,433),     S(252,209),     S(187,226),     S(239,318),     S(95,349),      S(175,329),     //
    S(-26,98),      S(140,156),     S(91,50),       S(188,-18),     S(108,-9),      S(11,48),       S(-48,95),      S(-97,51),      //
    S(-69,-62),     S(-36,-55),     S(-40,-105),    S(-40,-143),    S(-51,-124),    S(-97,-127),    S(-130,-57),    S(-165,-38),    //
    S(-56,-167),    S(-1,-130),     S(-49,-172),    S(-67,-162),    S(-65,-186),    S(-112,-169),   S(-155,-90),    S(-190,-107),   //
    S(-16,-206),    S(83,-195),     S(-13,-162),    S(-68,-142),    S(-87,-149),    S(-136,-154),   S(-141,-114),   S(-189,-128),   //
    S(-68,-202),    S(134,-213),    S(33,-173),     S(-83,-106),    S(-99,-159),    S(-142,-143),   S(-148,-99),    S(-191,-122),   //
};
const std::array<PScore, 64> KNIGHT_PSQT = {
    S(-328,-149),   S(22,-124),     S(-515,262),    S(33,63),       S(-226,142),    S(-273,161),    S(-246,-40),    S(-395,-8),     //
    S(60,-58),      S(68,81),       S(221,-34),     S(84,51),       S(160,61),      S(137,-50),     S(-4,-16),      S(69,-79),      //
    S(28,54),       S(64,129),      S(228,104),     S(150,80),      S(143,87),      S(62,70),       S(11,79),       S(-86,39),      //
    S(131,25),      S(10,115),      S(136,92),      S(58,121),      S(133,90),      S(56,85),       S(-22,42),      S(-9,56),       //
    S(52,38),       S(147,36),      S(59,70),       S(55,74),       S(20,94),       S(18,80),       S(-20,59),      S(-18,-38),     //
    S(-42,0),       S(-12,-18),     S(-37,-9),      S(0,58),        S(9,45),        S(-90,17),      S(-71,-14),     S(-102,-17),    //
    S(5,31),        S(22,18),       S(-41,0),       S(-47,17),      S(-50,-10),     S(-105,-7),     S(-84,-29),     S(-136,-108),   //
    S(-118,8),      S(-26,-49),     S(10,-74),      S(25,-33),      S(9,-43),       S(-38,-130),    S(-90,-11),     S(-227,0),      //
};
const std::array<PScore, 64> BISHOP_PSQT = {
    S(-149,62),     S(-74,10),      S(-568,115),    S(-270,83),     S(-353,136),    S(-452,113),    S(-50,85),      S(10,63),       //
    S(-67,-12),     S(-59,87),      S(13,33),       S(17,2),        S(-16,53),      S(-11,42),      S(0,21),        S(-118,37),     //
    S(-30,78),      S(29,68),       S(213,42),      S(78,50),       S(40,60),       S(-7,79),       S(92,11),       S(-8,42),       //
    S(33,-25),      S(13,48),       S(94,22),       S(70,65),       S(119,36),      S(23,57),       S(18,35),       S(-99,86),      //
    S(34,-49),      S(19,17),       S(29,23),       S(57,59),       S(31,89),       S(3,41),        S(-22,9),       S(-17,-56),     //
    S(60,-23),      S(79,-15),      S(82,-16),      S(11,48),       S(-5,58),       S(-32,66),      S(46,-25),      S(14,-51),      //
    S(-9,-49),      S(108,-49),     S(57,-37),      S(0,4),         S(-14,-16),     S(20,-18),      S(-22,-7),      S(49,-137),     //
    S(-1,53),       S(-11,16),      S(-19,36),      S(8,-54),       S(-32,-50),     S(6,-8),        S(1,-58),       S(-45,8),       //
};
const std::array<PScore, 64> ROOK_PSQT = {
    S(111,10),      S(307,-12),     S(15,83),       S(31,84),       S(93,44),       S(3,76),        S(69,52),       S(66,60),       //
    S(158,29),      S(123,69),      S(240,27),      S(101,107),     S(117,92),      S(15,121),      S(-15,114),     S(18,103),      //
    S(40,63),       S(263,2),       S(207,22),      S(207,15),      S(127,30),      S(41,95),       S(65,59),       S(-36,84),      //
    S(-13,61),      S(22,54),       S(47,56),       S(114,-3),      S(62,17),       S(-6,109),      S(-15,71),      S(-109,87),     //
    S(-103,-26),    S(28,-38),      S(-65,51),      S(-41,24),      S(-73,32),      S(-103,83),     S(-135,74),     S(-146,54),     //
    S(-112,-48),    S(27,-114),     S(-65,-22),     S(-81,-8),      S(-64,-34),     S(-136,38),     S(-144,13),     S(-165,13),     //
    S(-133,-4),     S(-34,-98),     S(-26,-74),     S(-48,-44),     S(-55,-41),     S(-94,-14),     S(-146,-31),    S(-162,-42),    //
    S(-125,-25),    S(-81,-2),      S(-54,-33),     S(-29,-43),     S(-57,-18),     S(-67,-27),     S(-85,-44),     S(-114,-34),    //
};
const std::array<PScore, 64> QUEEN_PSQT = {
    S(84,-8),       S(87,-36),      S(63,102),      S(41,75),       S(32,74),       S(-76,183),     S(4,41),        S(-44,-10),     //
    S(91,58),       S(-135,282),    S(4,238),       S(-183,398),    S(-106,276),    S(-168,283),    S(-113,139),    S(-48,65),      //
    S(10,160),      S(112,137),     S(134,188),     S(38,235),      S(-72,290),     S(-41,211),     S(0,85),        S(0,9),         //
    S(19,101),      S(34,151),      S(-23,183),     S(-53,274),     S(-70,254),     S(-33,114),     S(-4,53),       S(-42,69),      //
    S(-7,95),       S(51,47),       S(-35,196),     S(-39,175),     S(-74,183),     S(-64,121),     S(-16,-48),     S(-41,-20),     //
    S(27,-110),     S(28,-19),      S(9,49),        S(-46,91),      S(-23,8),       S(-23,-29),     S(-10,-68),     S(-43,-27),     //
    S(28,-233),     S(54,-312),     S(16,-146),     S(38,-95),      S(-14,-48),     S(16,-160),     S(-14,-108),    S(-68,-23),     //
    S(-132,-51),    S(-11,-428),    S(-28,-267),    S(0,-227),      S(28,-152),     S(42,-234),     S(-26,-126),    S(-88,-30),     //
};
const std::array<PScore, 64> KING_PSQT = {
    S(489,-612),    S(392,-172),    S(-523,166),    S(-550,164),    S(0,0),         S(0,0),         S(0,0),         S(0,0),         //
    S(174,-67),     S(-159,201),    S(-129,225),    S(-37,201),     S(0,0),         S(0,0),         S(0,0),         S(0,0),         //
    S(-170,68),     S(4,150),       S(59,135),      S(-46,111),     S(0,0),         S(0,0),         S(0,0),         S(0,0),         //
    S(-321,71),     S(-148,166),    S(3,123),       S(-91,106),     S(0,0),         S(0,0),         S(0,0),         S(0,0),         //
    S(-274,2),      S(-125,87),     S(-44,80),      S(-212,142),    S(0,0),         S(0,0),         S(0,0),         S(0,0),         //
    S(-179,-53),    S(29,-15),      S(-90,50),      S(-187,121),    S(0,0),         S(0,0),         S(0,0),         S(0,0),         //
    S(100,-139),    S(163,-74),     S(31,-1),       S(-100,68),     S(0,0),         S(0,0),         S(0,0),         S(0,0),         //
    S(29,-245),     S(120,-179),    S(-21,-127),    S(10,-163),     S(0,0),         S(0,0),         S(0,0),         S(0,0),         //
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
