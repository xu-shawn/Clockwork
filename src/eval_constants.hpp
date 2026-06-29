#pragma once

#include "eval_types.hpp"

namespace Clockwork {

// clang-format off
inline const PParam PAWN_MAT   = S(260, 553);
inline const PParam KNIGHT_MAT = S(1125, 1798);
inline const PParam BISHOP_MAT = S(1168, 1873);
inline const PParam ROOK_MAT   = S(1376, 2856);
inline const PParam QUEEN_MAT  = S(3051, 4309);

inline const PParam TEMPO_VAL  = S(113, 72);

inline const PParam BISHOP_XRAY_PAWNS   = S(-19, -1);
inline const PParam BISHOP_PAIR_VAL   = S(95, 264);
inline const PParam ROOK_OPEN_VAL     = S(142, -10);
inline const PParam ROOK_SEMIOPEN_VAL = S(58, 12);
inline const PParam MINOR_BEHIND_PAWN = S(24, 49);
inline const PParam RESTRICTED_SQUARES = S(25, 7);

inline const PParam DOUBLED_PAWN_VAL = S(-38, -95);
inline const PParam ISOLATED_PAWN_VAL = S(-18, -43);

inline const PParam POTENTIAL_CHECKER_VAL = S(-59, -49);
inline const PParam OUTPOST_KNIGHT_VAL    = S(70, 48);
inline const PParam OUTPOST_BISHOP_VAL    = S(59, 33);

inline const PParam PAWN_PUSH_THREAT_KNIGHT = S(54, 51);
inline const PParam PAWN_PUSH_THREAT_BISHOP = S(53, 3);
inline const PParam PAWN_PUSH_THREAT_ROOK   = S(25, 79);
inline const PParam PAWN_PUSH_THREAT_QUEEN  = S(84, -67);

inline const std::array<PParam, 6> PAWN_PHALANX = {
    S(20, 6), S(46, 40), S(82, 73), S(157, 253), S(526, 472), S(705, 804),
};
inline const std::array<PParam, 5> DEFENDED_PAWN = {
    S(57, 39), S(48, 28), S(75, 59), S(113, 215), S(530, 99),
};
inline const std::array<PParam, 6> PASSED_PAWN = {
    S(-115, -287), S(-118, -246), S(-85, -95), S(-33, 47), S(114, 243), S(315, 491),
};
inline const std::array<PParam, 6> PASSED_CLEAR_STOPPERS = {
    S(-97, 66), S(-93, 52), S(-49, 127), S(-67, 266), S(-12, 390), S(113, 251),
};
inline const std::array<PParam, 6> PASSED_CLEAR_FORWARD = {
    S(-17, 80), S(-25, 71), S(-49, 118), S(-19, 154), S(92, 192), S(41, 256),
};
inline const std::array<PParam, 6> DEFENDED_PASSED_PUSH = {
    S(28, -51), S(30, -8), S(16, 39), S(27, 120), S(77, 329), S(360, 282),
};
inline const std::array<PParam, 6> BLOCKED_PASSED_PAWN = {
    S(10, -49), S(1, 9), S(-8, -35), S(-5, -76), S(-27, -206), S(-256, -538),
};

inline const std::array<PParam, 8> FRIENDLY_KING_PASSED_PAWN_DISTANCE = {
    S(0, 0), S(28, 270), S(10, 211), S(2, 120), S(18, 72), S(29, 79), S(81, 71), S(73, 51),
};
inline const std::array<PParam, 8> ENEMY_KING_PASSED_PAWN_DISTANCE = {
    S(0, 0), S(-161, -53), S(12, -1), S(7, 105), S(38, 160), S(54, 201), S(65, 215), S(48, 193),
};

inline const std::array<PParam, 9> KNIGHT_MOBILITY = {
    S(-137, -410), S(-46, -131), S(-3, 12), S(32, 68), S(69, 112), S(92, 152), S(116, 163), S(137, 177), S(160, 130),
};
inline const std::array<PParam, 14> BISHOP_MOBILITY = {
    S(-94, -290), S(-20, -87), S(54, -2), S(83, 67), S(118, 109), S(135, 146), S(143, 176), S(148, 200), S(153, 219), S(162, 227), S(176, 219), S(190, 207), S(205, 190), S(171, 177),
};
inline const std::array<PParam, 15> ROOK_MOBILITY = {
    S(151, -159), S(45, 74), S(75, 111), S(97, 132), S(112, 154), S(119, 170), S(127, 188), S(135, 196), S(143, 209), S(150, 220), S(154, 230), S(156, 239), S(158, 247), S(168, 228), S(167, 209),
};
inline const std::array<PParam, 28> QUEEN_MOBILITY = {
    S(-181, -96), S(3, 67), S(43, 225), S(73, 377), S(98, 434), S(109, 502), S(122, 535), S(132, 561), S(140, 584), S(146, 606), S(154, 617), S(160, 627), S(166, 635), S(168, 641), S(170, 646), S(171, 644), S(167, 650), S(169, 645), S(172, 635), S(170, 632), S(163, 620), S(179, 590), S(133, 616), S(85, 604), S(42, 603), S(13, 626), S(-35, 651), S(-2, 583),
};

inline const PParam PAWN_THREAT_KNIGHT = S(294, 164);
inline const PParam PAWN_THREAT_BISHOP = S(243, 258);
inline const PParam PAWN_THREAT_ROOK   = S(265, 186);
inline const PParam PAWN_THREAT_QUEEN  = S(256, 13);

inline const std::array<PParam, 6> MINOR_THREAT = {
    S(14, 62), S(130, 123), S(149, 150), S(283, 153), S(268, 1), S(0, 0),
};
inline const std::array<PParam, 6> ROOK_THREAT = {
    S(12, 64), S(71, 120), S(103, 117), S(22, 14), S(264, -87), S(0, 0),
};
inline const PParam KING_THREAT  = S(9, 176);
inline const PParam HANGING_PAWN  = S(43, 104);
inline const PParam HANGING_NON_PAWN  = S(100, 43);

inline const std::array<PParam, 2> KNIGHT_ON_QUEEN = {
    S(33, -30), S(40, -14),
};
inline const std::array<PParam, 2> BISHOP_ON_QUEEN = {
    S(59, 48), S(135, -113),
};
inline const std::array<PParam, 2> ROOK_ON_QUEEN = {
    S(51, 10), S(74, -23),
};

inline const std::array<PParam, 9> BISHOP_PAWNS = {
    S(5, -19), S(5, -17), S(-2, -24), S(-9, -33), S(-17, -42), S(-23, -52), S(-28, -61), S(-34, -67), S(-42, -88),
};

inline const PParam ROOK_LINEUP = S(22, 99);

inline const std::array<PParam, 48> PAWN_PSQT = {
    S(246, 310),    S(82, 469),     S(105, 444),    S(214, 312),    S(282, 173),    S(185, 252),    S(161, 281),    S(302, 190),    //
    S(51, 78),      S(75, 126),     S(56, 79),      S(78, 4),       S(65, -40),     S(19, -3),      S(17, 40),      S(-20, 73),     //
    S(53, -2),      S(20, 9),       S(69, -29),     S(55, -60),     S(37, -76),     S(9, -60),      S(-35, -30),    S(-41, 14),     //
    S(-5, -72),     S(-35, -37),    S(10, -57),     S(-0, -66),     S(-23, -78),    S(-37, -67),    S(-98, -44),    S(-95, -37),    //
    S(-9, -109),    S(32, -113),    S(18, -36),     S(-6, -34),     S(-37, -45),    S(-58, -52),    S(-91, -62),    S(-99, -58),    //
    S(27, -108),    S(115, -101),   S(101, -35),    S(46, 1),       S(5, -16),      S(-19, -37),    S(-49, -45),    S(-68, -38),    //
};
inline const std::array<PParam, 64> KNIGHT_PSQT = {
    S(-337, -606),  S(-354, 111),   S(-434, 106),   S(23, 42),      S(-99, 55),     S(-335, 120),   S(-446, 125),   S(-466, -465),  //
    S(-1, -16),     S(-19, 52),     S(102, 27),     S(87, 85),      S(92, 87),      S(41, 63),      S(-33, 52),     S(-55, 50),     //
    S(34, -12),     S(44, 48),      S(86, 83),      S(85, 106),     S(64, 113),     S(25, 92),      S(3, 60),       S(-51, 34),     //
    S(128, 29),     S(121, 59),     S(136, 96),     S(135, 154),    S(142, 144),    S(101, 105),    S(74, 65),      S(61, 50),      //
    S(109, 28),     S(140, 17),     S(141, 60),     S(129, 107),    S(116, 108),    S(106, 84),     S(80, 40),      S(36, 57),      //
    S(26, -33),     S(62, -14),     S(77, 22),      S(98, 66),      S(89, 66),      S(50, 26),      S(26, -2),      S(-29, -19),    //
    S(51, -20),     S(55, -4),      S(48, -14),     S(62, 18),      S(50, 23),      S(14, -39),     S(-31, 6),      S(-68, -71),    //
    S(-71, -75),    S(21, -22),     S(41, -38),     S(74, -26),     S(43, 3),       S(1, -47),      S(-18, -14),    S(-94, -142),   //
};
inline const std::array<PParam, 64> BISHOP_PSQT = {
    S(-133, 22),    S(-208, 140),   S(-434, 212),   S(-277, 123),   S(-342, 185),   S(-350, 184),   S(-234, 158),   S(-139, 102),   //
    S(-41, 22),     S(-63, 125),    S(-38, 84),     S(-79, 115),    S(-78, 113),    S(-34, 84),     S(-7, 71),      S(-50, 68),     //
    S(59, 45),      S(31, 91),      S(65, 97),      S(39, 96),      S(32, 82),      S(30, 83),      S(22, 75),      S(12, 56),      //
    S(35, 25),      S(76, 48),      S(95, 61),      S(104, 89),     S(135, 74),     S(64, 56),      S(74, 27),      S(7, 37),       //
    S(70, -32),     S(73, 23),      S(111, 36),     S(135, 43),     S(115, 58),     S(102, 45),     S(41, 29),      S(26, -4),      //
    S(86, -20),     S(115, -11),    S(135, 21),     S(102, 53),     S(95, 38),      S(91, 41),      S(91, 17),      S(38, 5),       //
    S(66, -80),     S(159, -51),    S(96, 5),       S(79, 25),      S(52, 31),      S(75, -22),     S(79, -41),     S(68, -35),     //
    S(77, -68),     S(43, -11),     S(43, 28),      S(75, -10),     S(50, 16),      S(65, 44),      S(79, -4),      S(73, -47),     //
};
inline const std::array<PParam, 64> ROOK_PSQT = {
    S(247, 168),    S(270, 201),    S(204, 234),    S(188, 205),    S(262, 151),    S(235, 165),    S(251, 177),    S(221, 188),    //
    S(155, 222),    S(214, 221),    S(251, 202),    S(200, 181),    S(254, 159),    S(201, 196),    S(142, 236),    S(150, 230),    //
    S(113, 211),    S(253, 156),    S(259, 149),    S(241, 121),    S(255, 126),    S(189, 178),    S(182, 196),    S(125, 238),    //
    S(76, 174),     S(149, 187),    S(175, 160),    S(155, 156),    S(180, 145),    S(132, 196),    S(122, 211),    S(67, 229),     //
    S(51, 87),      S(115, 111),    S(101, 130),    S(73, 138),     S(80, 149),     S(65, 179),     S(43, 176),     S(25, 173),     //
    S(56, 3),       S(141, 22),     S(128, 59),     S(99, 78),      S(120, 72),     S(75, 119),     S(77, 102),     S(30, 101),     //
    S(-42, -6),     S(107, -47),    S(121, -2),     S(108, 33),     S(113, 35),     S(93, 53),      S(72, 47),      S(39, 40),      //
    S(25, -28),     S(50, 8),       S(132, -6),     S(143, -1),     S(143, 7),      S(119, 35),     S(111, 26),     S(84, 36),      //
};
inline const std::array<PParam, 64> QUEEN_PSQT = {
    S(133, 271),    S(207, 249),    S(109, 409),    S(51, 512),     S(110, 452),    S(126, 352),    S(141, 258),    S(43, 341),     //
    S(130, 287),    S(144, 365),    S(105, 445),    S(-38, 580),    S(23, 528),     S(80, 413),     S(121, 277),    S(86, 261),     //
    S(94, 310),     S(140, 369),    S(92, 478),     S(43, 516),     S(77, 488),     S(134, 348),    S(154, 258),    S(133, 183),    //
    S(83, 261),     S(86, 350),     S(55, 399),     S(45, 490),     S(58, 497),     S(87, 348),     S(137, 228),    S(103, 185),    //
    S(55, 247),     S(56, 263),     S(48, 324),     S(22, 407),     S(36, 436),     S(68, 351),     S(76, 260),     S(99, 160),     //
    S(58, 123),     S(90, 136),     S(89, 227),     S(61, 254),     S(74, 267),     S(79, 289),     S(105, 201),    S(85, 169),     //
    S(13, -52),     S(46, -31),     S(67, 38),      S(99, 88),      S(94, 132),     S(100, 101),    S(76, 129),     S(85, 115),     //
    S(-5, -18),     S(30, -228),    S(64, -204),    S(84, -78),     S(95, 19),      S(99, -18),     S(91, -10),     S(63, 36),      //
};
inline const std::array<PParam, 64> KING_PSQT = {
    S(36, -577),    S(539, 198),    S(356, 285),    S(-8, 243),     S(0, 0),        S(0, 0),        S(0, 0),        S(0, 0),        //
    S(356, -177),   S(421, 280),    S(239, 277),    S(-5, 214),     S(0, 0),        S(0, 0),        S(0, 0),        S(0, 0),        //
    S(224, 56),     S(272, 237),    S(114, 253),    S(-67, 211),    S(0, 0),        S(0, 0),        S(0, 0),        S(0, 0),        //
    S(32, 1),       S(126, 128),    S(-34, 202),    S(-152, 225),   S(0, 0),        S(0, 0),        S(0, 0),        S(0, 0),        //
    S(-156, -23),   S(-49, 84),     S(-150, 173),   S(-243, 226),   S(0, 0),        S(0, 0),        S(0, 0),        S(0, 0),        //
    S(-88, -57),    S(-5, 30),      S(-117, 139),   S(-182, 194),   S(0, 0),        S(0, 0),        S(0, 0),        S(0, 0),        //
    S(17, -120),    S(26, -20),     S(-58, 66),     S(-153, 134),   S(0, 0),        S(0, 0),        S(0, 0),        S(0, 0),        //
    S(-35, -258),   S(-7, -114),    S(-113, -23),   S(-108, -43),   S(0, 0),        S(0, 0),        S(0, 0),        S(0, 0),        //
};

inline const PParam KS_NO_QUEEN = S(-90, -455);

inline const std::array<PParam, 5> PT_INNER_RING_ATTACKS = {
    S(8, -6), S(10, 14), S(10, 4), S(4, 2), S(3, -10),
};
inline const std::array<PParam, 5> PT_OUTER_RING_ATTACKS = {
    S(4, -8), S(5, 4), S(2, 2), S(3, -0), S(3, -1),
};

inline const PParam KS_FLANK_ATTACK = S(3, -2);
inline const PParam KS_FLANK_DEFENSE = S(-3, -0);
inline const PParam KS_FLANK_DOUBLE_ATTACK   = S(3, -1);
inline const PParam KS_FLANK_DOUBLE_DEFENSE  = S(-2, 2);

inline const std::array<std::array<PParam, 7>, 4> KING_SHELTER = {{
  {{ S(16, -19), S(-7, 7), S(-4, -7), S(6, -15), S(12, -27), S(5, -52), S(-7, -48), }},
  {{ S(2, 5), S(-22, 1), S(-18, 10), S(-10, 17), S(-7, 11), S(-10, -13), S(-25, -19), }},
  {{ S(-4, 0), S(-12, -9), S(-13, 20), S(-8, 19), S(-6, 14), S(-8, -15), S(-29, -33), }},
  {{ S(5, 11), S(-10, 21), S(-8, 43), S(-2, 46), S(-2, 43), S(4, 19), S(4, -13), }},
}};
inline const std::array<PParam, 7> BLOCKED_SHELTER_STORM = {
    S(0, 0), S(0, 0), S(10, 26), S(-6, 4), S(-9, 11), S(-6, 29), S(3, 47),
};
inline const std::array<std::array<PParam, 7>, 4> SHELTER_STORM = {{
  {{ S(6, 9), S(-48, -139), S(-9, -40), S(-0, 6), S(-3, 5), S(-6, 10), S(-5, 9), }},
  {{ S(9, -1), S(-25, -151), S(-5, -30), S(-2, -1), S(-1, -1), S(-9, 5), S(1, 4), }},
  {{ S(-1, 11), S(-10, -70), S(5, -3), S(-0, 10), S(-4, 13), S(-11, 21), S(-7, 22), }},
  {{ S(1, -0), S(0, -47), S(-1, 36), S(-2, 27), S(-5, 8), S(-12, 12), S(-8, 20), }},
}};
inline TunableSigmoid<32> KING_SAFETY_ACTIVATION(
        1684, 1020, -17, -5
);

inline VParam WINNABLE_PAWNS = V(-18);
inline VParam WINNABLE_SYM = V(130);
inline VParam WINNABLE_ASYM = V(112);
inline VParam WINNABLE_PAWN_ENDGAME = V(120);
inline VParam WINNABLE_BIAS = V(-586);

// Epoch duration: 5.4519s
}  // namespace Clockwork
