//
//  Type.hpp
//  Blackbird
//
//  Created by Mathias Dietrich on 6/18/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

#ifndef Type_h
#define Type_h

typedef int PIECE;

#define SELECTED 1
#define OPTION 2

typedef unsigned long long U64;

#define W_KING 1
#define W_QUEEN 2
#define W_BISHOP 3
#define W_KNIGHT 4
#define W_ROOK 5
#define W_PAWN 6
#define B_KING -1
#define B_QUEEN -2
#define B_BISHOP -3
#define B_KNIGHT -4
#define B_ROOK -5
#define B_PAWN -6
#define EMPTY 0

#define WHITE 0
#define BLACK 1

#define VAL_KING 40000
#define VAL_QUEEN 9940
#define VAL_BISHOP 3500
#define VAL_KNIGHT 3050
#define VAL_ROOK 5480
#define VAL_PAWN 1000
#define VAL_BISHOPTWO 7450;

#define BB uint64_t

const BB FileABB = 0x0101010101010101ULL;
const BB FileBBB = FileABB << 1;
const BB FileCBB = FileABB << 2;
const BB FileDBB = FileABB << 3;
const BB FileEBB = FileABB << 4;
const BB FileFBB = FileABB << 5;
const BB FileGBB = FileABB << 6;
const BB FileHBB = FileABB << 7;

const BB Rank1BB = 0xFF;
const BB Rank2BB = Rank1BB << (8 * 1);
const BB Rank3BB = Rank1BB << (8 * 2);
const BB Rank4BB = Rank1BB << (8 * 3);
const BB Rank5BB = Rank1BB << (8 * 4);
const BB Rank6BB = Rank1BB << (8 * 5);
const BB Rank7BB = Rank1BB << (8 * 6);
const BB Rank8BB = Rank1BB << (8 * 7);

enum CASTLE { NONE, CWK, CWQ, CBK, CBQ };

enum WINSTATE {PNG, ENGINE, DEBUGWIN};
    
enum Square {
    a1, b1, c1, d1, e1, f1, g1, h1,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a8, b8, c8, d8, e8, f8, g8, h8};

enum File {FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE };

enum Rank {Rank_1, Rank_2,Rank_3, Rank_4,Rank_5, Rank_6, Rank_7, Rank_8, Rank_NONE};

enum SquareDelta {
    DELTA_SSW = -021, DELTA_SS = -020, DELTA_SSE = -017, DELTA_SWW = -012,
    DELTA_SW = -011, DELTA_S = -010, DELTA_SE = -07, DELTA_SEE = -06,
    DELTA_W = -01, DELTA_ZERO = 0, DELTA_E = 01, DELTA_NWW = 06, DELTA_NW = 07,
    DELTA_N = 010, DELTA_NE = 011, DELTA_NEE = 012, DELTA_NNW = 017,
    DELTA_NN = 020, DELTA_NNE = 021
};
#endif /* Type_h */
