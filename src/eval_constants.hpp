#pragma once

#include "eval_types.hpp"

namespace Clockwork {

// clang-format off
inline const PParam PAWN_MAT   = S(221, 522);
inline const PParam KNIGHT_MAT = S(944, 1699);
inline const PParam BISHOP_MAT = S(983, 1772);
inline const PParam ROOK_MAT   = S(1156, 2703);
inline const PParam QUEEN_MAT  = S(2626, 4053);

inline const PParam TEMPO_VAL  = S(108, 66);

inline const PParam BISHOP_XRAY_PAWNS   = S(-16, -2);
inline const PParam BISHOP_PAIR_VAL   = S(73, 248);
inline const PParam ROOK_OPEN_VAL     = S(118, -4);
inline const PParam ROOK_SEMIOPEN_VAL = S(48, 13);
inline const PParam MINOR_BEHIND_PAWN = S(20, 48);
inline const PParam RESTRICTED_SQUARES = S(21, 8);

inline const PParam DOUBLED_PAWN_VAL = S(-28, -93);
inline const PParam ISOLATED_PAWN_VAL = S(-15, -40);

inline const PParam POTENTIAL_CHECKER_VAL = S(-44, -46);
inline const PParam OUTPOST_KNIGHT_VAL    = S(67, 51);
inline const PParam OUTPOST_BISHOP_VAL    = S(54, 36);

inline const PParam PAWN_PUSH_THREAT_KNIGHT = S(48, 52);
inline const PParam PAWN_PUSH_THREAT_BISHOP = S(45, 8);
inline const PParam PAWN_PUSH_THREAT_ROOK   = S(22, 80);
inline const PParam PAWN_PUSH_THREAT_QUEEN  = S(70, -51);

inline const std::array<PParam, 6> PAWN_PHALANX = {
    S(18, 9), S(38, 38), S(66, 74), S(121, 232), S(418, 388), S(497, 682),
};
inline const std::array<PParam, 5> DEFENDED_PAWN = {
    S(50, 40), S(42, 29), S(63, 55), S(93, 192), S(419, 91),
};
inline const std::array<PParam, 6> PASSED_PAWN = {
    S(-91, -275), S(-95, -238), S(-69, -96), S(-24, 37), S(92, 225), S(226, 468),
};
inline const std::array<PParam, 6> PASSED_CLEAR_STOPPERS = {
    S(-117, 66), S(-113, 67), S(-94, 145), S(-114, 283), S(-46, 400), S(114, 264),
};
inline const std::array<PParam, 6> PASSED_CLEAR_FORWARD = {
    S(-37, 82), S(-42, 75), S(-68, 123), S(-34, 159), S(68, 203), S(17, 271),
};
inline const std::array<PParam, 6> DEFENDED_PASSED_PUSH = {
    S(25, -44), S(28, -4), S(11, 39), S(20, 115), S(58, 306), S(277, 265),
};
inline const std::array<PParam, 6> BLOCKED_PASSED_PAWN = {
    S(12, -42), S(-2, 12), S(-9, -37), S(-6, -82), S(-11, -209), S(-153, -569),
};

inline const std::array<PParam, 8> FRIENDLY_KING_PASSED_PAWN_DISTANCE = {
    S(0, 0), S(14, 248), S(3, 194), S(-2, 111), S(10, 72), S(22, 77), S(67, 74), S(57, 54),
};
inline const std::array<PParam, 8> ENEMY_KING_PASSED_PAWN_DISTANCE = {
    S(0, 0), S(-123, -42), S(6, 3), S(4, 100), S(29, 152), S(41, 192), S(49, 205), S(40, 184),
};

inline const std::array<PParam, 9> KNIGHT_MOBILITY = {
    S(-119, -293), S(-53, -128), S(-15, -1), S(15, 49), S(45, 88), S(64, 126), S(85, 136), S(105, 147), S(125, 104),
};
inline const std::array<PParam, 14> BISHOP_MOBILITY = {
    S(-73, -250), S(-19, -91), S(38, -7), S(61, 53), S(89, 91), S(103, 124), S(109, 151), S(114, 172), S(119, 188), S(127, 195), S(138, 189), S(150, 176), S(162, 167), S(134, 147),
};
inline const std::array<PParam, 15> ROOK_MOBILITY = {
    S(108, -125), S(26, 51), S(50, 87), S(69, 109), S(82, 130), S(87, 146), S(93, 163), S(100, 171), S(106, 183), S(112, 193), S(116, 203), S(118, 212), S(119, 219), S(129, 202), S(129, 187),
};
inline const std::array<PParam, 28> QUEEN_MOBILITY = {
    S(-134, 37), S(-50, 171), S(-22, 272), S(-0, 371), S(18, 413), S(27, 461), S(37, 489), S(46, 507), S(52, 527), S(58, 543), S(65, 555), S(71, 562), S(75, 570), S(78, 576), S(78, 583), S(80, 582), S(77, 589), S(80, 584), S(83, 577), S(82, 573), S(79, 564), S(88, 539), S(56, 558), S(12, 553), S(-28, 551), S(-54, 573), S(-101, 605), S(-65, 527),
};

inline const PParam PAWN_THREAT_KNIGHT = S(264, 182);
inline const PParam PAWN_THREAT_BISHOP = S(220, 247);
inline const PParam PAWN_THREAT_ROOK   = S(220, 186);
inline const PParam PAWN_THREAT_QUEEN  = S(235, -6);

inline const std::array<PParam, 6> MINOR_THREAT = {
    S(11, 59), S(106, 118), S(119, 140), S(232, 148), S(214, -6), S(0, 0),
};
inline const std::array<PParam, 6> ROOK_THREAT = {
    S(8, 63), S(60, 121), S(84, 123), S(12, 14), S(193, -40), S(0, 0),
};
inline const PParam KING_THREAT  = S(13, 175);
inline const PParam HANGING_PAWN  = S(40, 99);
inline const PParam HANGING_NON_PAWN  = S(80, 47);

inline const std::array<PParam, 2> KNIGHT_ON_QUEEN = {
    S(27, -18), S(34, -18),
};
inline const std::array<PParam, 2> BISHOP_ON_QUEEN = {
    S(47, 53), S(101, -73),
};
inline const std::array<PParam, 2> ROOK_ON_QUEEN = {
    S(42, 8), S(43, -5),
};

inline const std::array<PParam, 9> BISHOP_PAWNS = {
    S(3, -15), S(3, -15), S(-2, -22), S(-8, -31), S(-14, -40), S(-19, -50), S(-23, -59), S(-26, -66), S(-33, -88),
};

inline const PParam ROOK_LINEUP = S(17, 83);

inline const std::array<PParam, 48> PAWN_PSQT = {
    S(187, 314),    S(43, 451),     S(59, 416),     S(136, 302),    S(200, 176),    S(141, 236),    S(137, 251),    S(254, 187),    //
    S(46, 63),      S(46, 113),     S(36, 68),      S(53, -5),      S(45, -46),     S(16, -17),     S(9, 26),       S(-13, 59),     //
    S(41, -6),      S(11, 3),       S(52, -34),     S(41, -60),     S(29, -76),     S(6, -63),      S(-31, -34),    S(-36, 6),      //
    S(-5, -75),     S(-32, -42),    S(7, -60),      S(-3, -65),     S(-24, -77),    S(-34, -69),    S(-81, -52),    S(-80, -42),    //
    S(-7, -108),    S(23, -105),    S(14, -39),     S(-6, -39),     S(-34, -49),    S(-52, -57),    S(-78, -69),    S(-82, -64),    //
    S(24, -108),    S(89, -93),     S(82, -36),     S(35, -7),      S(-2, -22),     S(-19, -43),    S(-43, -53),    S(-56, -48),    //
};
inline const std::array<PParam, 64> KNIGHT_PSQT = {
    S(-296, -562),  S(-331, 55),    S(-406, 57),    S(-53, 25),     S(-143, 37),    S(-334, 86),    S(-391, 70),    S(-394, -448),  //
    S(-32, -20),    S(-33, 37),     S(49, 29),      S(42, 67),      S(40, 69),      S(17, 40),      S(-37, 35),     S(-71, 33),     //
    S(9, -21),      S(5, 49),       S(43, 83),      S(50, 99),      S(39, 99),      S(3, 81),       S(-14, 46),     S(-49, 8),      //
    S(101, 24),     S(97, 57),      S(115, 93),     S(112, 142),    S(117, 132),    S(84, 97),      S(59, 55),      S(47, 40),      //
    S(84, 26),      S(116, 19),     S(127, 60),     S(110, 102),    S(96, 105),     S(91, 79),      S(65, 33),      S(27, 41),      //
    S(20, -27),     S(53, -8),      S(65, 31),      S(85, 68),      S(73, 68),      S(41, 27),      S(20, -3),      S(-25, -28),    //
    S(45, -20),     S(58, -7),      S(44, -7),      S(55, 16),      S(42, 20),      S(14, -33),     S(-27, -4),     S(-54, -74),    //
    S(-54, -85),    S(23, -23),     S(41, -34),     S(66, -21),     S(40, -9),      S(4, -52),      S(-10, -26),    S(-66, -149),   //
};
inline const std::array<PParam, 64> BISHOP_PSQT = {
    S(-117, -24),   S(-202, 109),   S(-375, 164),   S(-271, 109),   S(-310, 149),   S(-303, 139),   S(-210, 121),   S(-112, 47),    //
    S(-52, 7),      S(-72, 106),    S(-49, 72),     S(-96, 94),     S(-89, 90),     S(-44, 66),     S(-12, 55),     S(-50, 46),     //
    S(38, 31),      S(15, 76),      S(35, 91),      S(18, 88),      S(18, 66),      S(21, 63),      S(11, 60),      S(6, 34),       //
    S(23, 11),      S(56, 43),      S(76, 59),      S(83, 80),      S(111, 64),     S(52, 47),      S(56, 23),      S(3, 21),       //
    S(56, -41),     S(65, 14),      S(89, 35),      S(113, 40),     S(94, 53),      S(84, 41),      S(33, 22),      S(26, -16),     //
    S(65, -21),     S(98, -11),     S(116, 21),     S(84, 51),      S(79, 36),      S(77, 38),      S(79, 13),      S(29, -1),      //
    S(60, -66),     S(129, -42),    S(86, -2),      S(67, 18),      S(42, 24),      S(66, -20),     S(66, -34),     S(61, -32),     //
    S(59, -49),     S(47, -19),     S(40, 16),      S(71, -15),     S(46, 11),      S(54, 36),      S(73, -11),     S(58, -27),     //
};
inline const std::array<PParam, 64> ROOK_PSQT = {
    S(170, 157),    S(197, 178),    S(141, 209),    S(118, 179),    S(185, 137),    S(165, 148),    S(174, 166),    S(152, 174),    //
    S(118, 197),    S(165, 200),    S(188, 187),    S(146, 163),    S(193, 144),    S(152, 173),    S(104, 208),    S(107, 206),    //
    S(90, 183),     S(211, 136),    S(207, 135),    S(186, 118),    S(205, 114),    S(152, 157),    S(150, 171),    S(90, 211),     //
    S(60, 148),     S(121, 162),    S(141, 142),    S(119, 142),    S(143, 133),    S(107, 173),    S(95, 186),     S(51, 200),     //
    S(37, 74),      S(90, 96),      S(78, 114),     S(58, 121),     S(65, 131),     S(50, 157),     S(31, 153),     S(14, 147),     //
    S(41, 2),       S(116, 21),     S(103, 52),     S(79, 66),      S(96, 65),      S(58, 102),     S(62, 85),      S(17, 83),      //
    S(-43, -9),     S(96, -37),     S(99, 0),       S(90, 28),      S(95, 31),      S(81, 42),      S(61, 38),      S(33, 25),      //
    S(17, -37),     S(29, 7),       S(106, -8),     S(121, -9),     S(116, 3),      S(97, 24),      S(93, 13),      S(73, 16),      //
};
inline const std::array<PParam, 64> QUEEN_PSQT = {
    S(79, 193),     S(135, 202),    S(56, 343),     S(-2, 444),     S(48, 402),     S(62, 317),     S(84, 213),     S(10, 252),     //
    S(66, 241),     S(98, 299),     S(46, 407),     S(-76, 519),    S(-26, 481),    S(32, 366),     S(78, 221),     S(41, 216),     //
    S(47, 265),     S(88, 337),     S(50, 432),     S(4, 475),      S(35, 441),     S(88, 310),     S(101, 226),    S(80, 160),     //
    S(38, 233),     S(41, 330),     S(18, 383),     S(13, 448),     S(20, 455),     S(51, 319),     S(86, 215),     S(63, 155),     //
    S(18, 217),     S(20, 244),     S(16, 304),     S(-2, 367),     S(10, 388),     S(36, 311),     S(45, 222),     S(58, 141),     //
    S(21, 105),     S(50, 146),     S(49, 223),     S(28, 240),     S(37, 248),     S(45, 257),     S(66, 186),     S(50, 142),     //
    S(-16, -42),    S(18, -5),      S(33, 55),      S(59, 89),      S(55, 127),     S(59, 107),     S(43, 123),     S(46, 113),     //
    S(-44, -47),    S(-2, -209),    S(18, -145),    S(44, -42),     S(54, 28),      S(61, 4),       S(51, 14),      S(21, 45),      //
};
inline const std::array<PParam, 64> KING_PSQT = {
    S(92, -565),    S(475, 169),    S(320, 239),    S(-4, 208),     S(0, 0),        S(0, 0),        S(0, 0),        S(0, 0),        //
    S(325, -167),   S(359, 243),    S(201, 235),    S(1, 181),      S(0, 0),        S(0, 0),        S(0, 0),        S(0, 0),        //
    S(197, 39),     S(225, 211),    S(67, 231),     S(-83, 199),    S(0, 0),        S(0, 0),        S(0, 0),        S(0, 0),        //
    S(43, -6),      S(91, 127),     S(-51, 188),    S(-150, 208),   S(0, 0),        S(0, 0),        S(0, 0),        S(0, 0),        //
    S(-108, -35),   S(-46, 74),     S(-145, 158),   S(-224, 203),   S(0, 0),        S(0, 0),        S(0, 0),        S(0, 0),        //
    S(-62, -57),    S(-12, 30),     S(-108, 123),   S(-161, 167),   S(0, 0),        S(0, 0),        S(0, 0),        S(0, 0),        //
    S(15, -107),    S(17, -15),     S(-59, 62),     S(-135, 114),   S(0, 0),        S(0, 0),        S(0, 0),        S(0, 0),        //
    S(-19, -230),   S(-8, -101),    S(-99, -25),    S(-96, -44),    S(0, 0),        S(0, 0),        S(0, 0),        S(0, 0),        //
};

inline const PParam KS_NO_QUEEN = S(-87, -451);

inline const std::array<PParam, 5> PT_INNER_RING_ATTACKS = {
    S(7, -6), S(9, 13), S(9, 4), S(4, 2), S(3, -9),
};
inline const std::array<PParam, 5> PT_OUTER_RING_ATTACKS = {
    S(4, -8), S(4, 5), S(2, 2), S(3, -0), S(3, -2),
};

inline const PParam KS_FLANK_ATTACK = S(3, -2);
inline const PParam KS_FLANK_DEFENSE = S(-3, 0);
inline const PParam KS_FLANK_DOUBLE_ATTACK   = S(2, -1);
inline const PParam KS_FLANK_DOUBLE_DEFENSE  = S(-2, 2);

inline const std::array<std::array<PParam, 7>, 4> KING_SHELTER = {{
  {{ S(17, -20), S(-6, 6), S(-3, -7), S(7, -15), S(12, -26), S(7, -50), S(-6, -50), }},
  {{ S(1, 6), S(-23, 2), S(-18, 11), S(-11, 18), S(-8, 12), S(-9, -10), S(-22, -19), }},
  {{ S(-3, 0), S(-12, -9), S(-13, 19), S(-8, 20), S(-6, 14), S(-8, -11), S(-28, -24), }},
  {{ S(6, 9), S(-10, 18), S(-8, 41), S(-3, 43), S(-2, 38), S(3, 17), S(2, -8), }},
}};
inline const std::array<PParam, 7> BLOCKED_SHELTER_STORM = {
    S(0, 0), S(0, 0), S(9, 24), S(-5, 4), S(-7, 10), S(-5, 26), S(4, 43),
};
inline const std::array<std::array<PParam, 7>, 4> SHELTER_STORM = {{
  {{ S(7, 8), S(-52, -115), S(-12, -29), S(-1, 5), S(-1, 3), S(-4, 7), S(-3, 7), }},
  {{ S(9, 0), S(-24, -111), S(-7, -20), S(-2, 3), S(0, -1), S(-7, 4), S(2, 3), }},
  {{ S(1, 12), S(-11, -46), S(3, -3), S(-1, 13), S(-2, 11), S(-9, 19), S(-5, 21), }},
  {{ S(2, -0), S(-3, -33), S(-4, 31), S(-3, 26), S(-4, 9), S(-10, 10), S(-6, 18), }},
}};
inline TunableSigmoid<32> KING_SAFETY_ACTIVATION(
        1468, 946, -15, -10
);

inline VParam WINNABLE_PAWNS = V(-17);
inline VParam WINNABLE_SYM = V(115);
inline VParam WINNABLE_ASYM = V(95);
inline VParam WINNABLE_PAWN_ENDGAME = V(94);
inline VParam WINNABLE_BIAS = V(-481);

// Epoch duration: 5.91993s
}  // namespace Clockwork
