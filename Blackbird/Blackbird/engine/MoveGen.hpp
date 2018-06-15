//
//  MoveGen.hpp
//  Blackbird
//
//  Created by Mathias Dietrich on 6/15/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
// https://github.com/syzygy1/tb/tree/master/src

#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

#include "Const.h"
#include "Helper.hpp"
#include "Board.hpp"
#include "m42.h"

using namespace std;

class MoveGen{
public:
    
    uint64_t w_prawnMoves[64];
    uint64_t b_prawnMoves[64];
    
    uint64_t w_prawnCatch[64];
    uint64_t b_prawnCatch[64];
    
    uint64_t knight[64];
    
    MoveGen(){
        
        M42::init();
        
        // Pawn Move
        uint64_t s = 1;
        for(int i=0;i<64;i++){
            w_prawnMoves[i] = 0;
            b_prawnMoves[i] = 0;
            w_prawnCatch[i] = 0;
            b_prawnCatch[i] = 0;
            knight[i] = 0;
        }
        w_prawnMoves[8] = s << 16 | s << 24;
        w_prawnMoves[9] = s << 17 | s << 25;
        w_prawnMoves[10] = s << 18 | s << 26;
        w_prawnMoves[11] = s << 19 | s << 27;
        w_prawnMoves[12] = s << 20 | s << 28;
        w_prawnMoves[13] = s << 21 | s << 29;
        w_prawnMoves[14] = s << 22 | s << 30;
        w_prawnMoves[15] = s << 23 | s << 31;
        w_prawnMoves[16] = s << 24;
        w_prawnMoves[17] = s << 25;
        w_prawnMoves[18] = s << 26;
        w_prawnMoves[19] = s << 27;
        w_prawnMoves[20] = s << 28;
        w_prawnMoves[21] = s << 29;
        w_prawnMoves[22] = s << 30;
        w_prawnMoves[23] = s << 31;
        w_prawnMoves[24] = s << 32;
        w_prawnMoves[25] = s << 33;
        w_prawnMoves[26] = s << 34;
        w_prawnMoves[27] = s << 35;
        w_prawnMoves[28] = s << 36;
        w_prawnMoves[29] = s << 37;
        w_prawnMoves[30] = s << 38;
        w_prawnMoves[31] = s << 39;
        w_prawnMoves[32] = s << 40;
        
        w_prawnMoves[33] = s << 41;
        w_prawnMoves[34] = s << 42;
        w_prawnMoves[35] = s << 43;
        w_prawnMoves[36] = s << 44;
        w_prawnMoves[37] = s << 45;
        w_prawnMoves[38] = s << 46;
        w_prawnMoves[39] = s << 47;
        w_prawnMoves[40] = s << 48;
        w_prawnMoves[41] = s << 49;
        w_prawnMoves[42] = s << 50;
        w_prawnMoves[43] = s << 51;
        w_prawnMoves[44] = s << 52;
        w_prawnMoves[45] = s << 53;
        w_prawnMoves[46] = s << 54;
        w_prawnMoves[47] = s << 55;
        w_prawnMoves[48] = s << 56;
        w_prawnMoves[49] = s << 57;
        w_prawnMoves[50] = s << 58;
        w_prawnMoves[51] = s << 59;
        w_prawnMoves[52] = s << 60;
        w_prawnMoves[53] = s << 61;
        w_prawnMoves[54] = s << 62;
        w_prawnMoves[55] = s << 63;
        
        
        b_prawnMoves[48] = s << 32 | s << 40;
        b_prawnMoves[49] = s << 33 | s << 41;
        b_prawnMoves[50] = s << 34 | s << 42;
        b_prawnMoves[51] = s << 35 | s << 43;
        b_prawnMoves[52] = s << 36 | s << 44;
        b_prawnMoves[53] = s << 37 | s << 45;
        b_prawnMoves[54] = s << 38 | s << 46;
        b_prawnMoves[55] = s << 39 | s << 47;
        
        b_prawnMoves[47] = s << 39;
        b_prawnMoves[46] = s << 38;
        b_prawnMoves[45] = s << 37;
        b_prawnMoves[44] = s << 36;
        b_prawnMoves[43] = s << 35;
        b_prawnMoves[42] = s << 34;
        b_prawnMoves[41] = s << 33;
        b_prawnMoves[40] = s << 32;
        b_prawnMoves[39] = s << 31;
        b_prawnMoves[38] = s << 30;
        b_prawnMoves[37] = s << 29;
        b_prawnMoves[36] = s << 28;
        b_prawnMoves[35] = s << 27;
        b_prawnMoves[34] = s << 26;
        b_prawnMoves[33] = s << 25;
        b_prawnMoves[32] = s << 24;
        b_prawnMoves[31] = s << 23;
        b_prawnMoves[30] = s << 22;
        b_prawnMoves[29] = s << 21;
        b_prawnMoves[28] = s << 20;
        b_prawnMoves[27] = s << 19;
        b_prawnMoves[26] = s << 18;
        b_prawnMoves[25] = s << 17;
        b_prawnMoves[24] = s << 16;
        b_prawnMoves[23] = s << 15;
        b_prawnMoves[22] = s << 14;
        b_prawnMoves[21] = s << 13;
        b_prawnMoves[20] = s << 12;
        b_prawnMoves[19] = s << 11;
        b_prawnMoves[18] = s << 10;
        b_prawnMoves[17] = s << 9;
        b_prawnMoves[16] = s << 8;
        b_prawnMoves[15] = s << 7;
        b_prawnMoves[14] = s << 6;
        b_prawnMoves[13] = s << 5;
        b_prawnMoves[12] = s << 4;
        b_prawnMoves[11] = s << 3;
        b_prawnMoves[10] = s << 2;
        b_prawnMoves[9]  = s << 1;
        b_prawnMoves[8]  = s << 0;
        
        // Pawn Catch
        w_prawnCatch[8] = s << 17;
        w_prawnCatch[9] = s << 16 | s << 18;
        w_prawnCatch[10] = s << 17 | s << 19;
        w_prawnCatch[11] = s << 18 | s << 20;
        w_prawnCatch[12] = s << 19 | s << 21;
        w_prawnCatch[13] = s << 20 | s << 22;
        w_prawnCatch[14] = s << 21 | s << 23;
        w_prawnCatch[15] = s << 22;
        w_prawnCatch[16] = s << 25;
        w_prawnCatch[17] = s << 24 | s << 26;
        w_prawnCatch[18] = s << 25 | s << 27;
        w_prawnCatch[19] = s << 26 | s << 28;
        w_prawnCatch[20] = s << 27 | s << 29;
        w_prawnCatch[21] = s << 28 | s << 30;
        w_prawnCatch[22] = s << 29 | s << 31;
        w_prawnCatch[23] = s << 30;
        w_prawnCatch[24] = s << 33;
        w_prawnCatch[25] = s << 32 | s << 34;
        w_prawnCatch[26] = s << 33 | s << 35;
        w_prawnCatch[27] = s << 34 | s << 36;
        w_prawnCatch[28] = s << 35 | s << 37;
        w_prawnCatch[29] = s << 36 | s << 38;
        w_prawnCatch[30] = s << 37 | s << 39;
        w_prawnCatch[31] = s << 38;
        w_prawnCatch[32] = s << 41;
        w_prawnCatch[33] = s << 40 | s << 42;
        w_prawnCatch[34] = s << 41 | s << 43;
        w_prawnCatch[35] = s << 42 | s << 44;
        w_prawnCatch[36] = s << 43 | s << 45;
        w_prawnCatch[37] = s << 44 | s << 46;
        w_prawnCatch[38] = s << 45 | s << 47;
        w_prawnCatch[39] = s << 46;
        w_prawnCatch[40] = s << 49;
        w_prawnCatch[41] = s << 48 | s << 50;
        w_prawnCatch[42] = s << 49 | s << 51;
        w_prawnCatch[43] = s << 50 | s << 52;
        w_prawnCatch[44] = s << 51 | s << 53;
        w_prawnCatch[45] = s << 52 | s << 54;
        w_prawnCatch[46] = s << 53 | s << 55;
        w_prawnCatch[47] = s << 54;
        w_prawnCatch[48] = s << 57;
        w_prawnCatch[49] = s << 56 | s << 58;
        w_prawnCatch[50] = s << 57 | s << 59;
        w_prawnCatch[51] = s << 58 | s << 60;
        w_prawnCatch[52] = s << 59 | s << 61;
        w_prawnCatch[53] = s << 60 | s << 62;
        w_prawnCatch[54] = s << 61 | s << 63;
        w_prawnCatch[55] = s << 62;
        
        b_prawnCatch[55] = s << 46;
        b_prawnCatch[54] = s << 45 | s << 47;
        b_prawnCatch[53] = s << 44 | s << 46;
        b_prawnCatch[52] = s << 43 | s << 45;
        b_prawnCatch[51] = s << 42 | s << 44;
        b_prawnCatch[50] = s << 41 | s << 43;
        b_prawnCatch[49] = s << 40 | s << 42;
        b_prawnCatch[48] = s << 41;
        b_prawnCatch[47] = s << 38;
        b_prawnCatch[46] = s << 37 | s << 39;
        b_prawnCatch[45] = s << 36 | s << 38;
        b_prawnCatch[44] = s << 35 | s << 37;
        b_prawnCatch[43] = s << 34 | s << 36;
        b_prawnCatch[42] = s << 33 | s << 35;
        b_prawnCatch[41] = s << 32 | s << 34;
        b_prawnCatch[40] = s << 33;
        b_prawnCatch[39] = s << 30;
        b_prawnCatch[38] = s << 29 | s << 31;
        b_prawnCatch[37] = s << 28 | s << 30;
        b_prawnCatch[36] = s << 27 | s << 29;
        b_prawnCatch[35] = s << 26 | s << 28;
        b_prawnCatch[34] = s << 25 | s << 27;
        b_prawnCatch[33] = s << 24 | s << 26;
        b_prawnCatch[32] = s << 25;
        b_prawnCatch[31] = s << 22;
        b_prawnCatch[30] = s << 21 | s << 23;
        b_prawnCatch[29] = s << 20 | s << 22;
        b_prawnCatch[28] = s << 19 | s << 21;
        b_prawnCatch[27] = s << 18 | s << 20;
        b_prawnCatch[26] = s << 17 | s << 19;
        b_prawnCatch[25] = s << 16 | s << 18;
        b_prawnCatch[24] = s << 17;
        b_prawnCatch[23] = s << 14;
        b_prawnCatch[22] = s << 13 | s << 15;
        b_prawnCatch[21] = s << 12 | s << 14;
        b_prawnCatch[20] = s << 11 | s << 13;
        b_prawnCatch[19] = s << 10 | s << 12;
        b_prawnCatch[18] = s << 9 | s << 11;
        b_prawnCatch[17] = s << 8 | s << 10;
        b_prawnCatch[16] = s << 9;
        b_prawnCatch[15] = s << 6;
        b_prawnCatch[14] = s << 5 | s << 7;
        b_prawnCatch[13] = s << 4 | s << 6;
        b_prawnCatch[12] = s << 3 | s << 5;
        b_prawnCatch[11] = s << 2 | s << 4;
        b_prawnCatch[10] = s << 1 | s << 3;
        b_prawnCatch[9] = s << 0 | s << 2;
        b_prawnCatch[8] = s << 1;
        
        // knights
        knight[0] = s << 17 | s << 10;
        knight[1] = s << 16 | s << 18 | s << 11;
        knight[2] = s << 8 | s << 17 | s << 19 | s << 12;
        knight[3] = s << 9 | s << 18 | s << 20 | s << 13;
        knight[4] = s << 10 | s << 19 | s << 21 | s << 14;
        knight[5] = s << 11 | s << 20 | s << 22 | s << 15;
        knight[6] = s << 12 | s << 21 | s << 23;
        knight[7] = s << 13 | s << 22;
        knight[8] = s << 25 | s << 18 | s << 2;
        knight[9] = s << 24 | s << 26 | s << 19 | s << 3;
        knight[10] = s << 0 | s << 16 | s << 25 | s << 27 | s << 20 | s << 4;
        knight[11] = s << 1 | s << 17 | s << 26 | s << 28 | s << 21 | s << 5;
        knight[12] = s << 2 | s << 18 | s << 27 | s << 29 | s << 22 | s << 6;
        knight[13] = s << 3 | s << 19 | s << 28 | s<< 30 | s < 23 | s << 7;
        knight[14] = s << 4 | s << 20 | s << 29 | s<< 31;
        knight[15] = s << 5 | s << 21 | s << 30;
        knight[16] = s << 33 | s << 26 | s << 10 | s<< 1;
        knight[17] = s << 0 | s << 32 | s << 34 | s<< 27 | s << 11 | s << 2;
        knight[18] = s << 1 | s << 8 | s << 24 | s<< 33 | s << 35 | s << 28 | s << 12 | s << 3;
        knight[19] = s << 2 | s << 9 | s << 25 | s<< 34 | s << 36 | s << 29 | s | 13 | s << 4;
        knight[20] = s << 3 | s << 10 | s << 26 | s<< 35 | s << 37 | s << 30 | s << 14 | s << 5;
        knight[21] = s << 4 | s << 11  | s << 27 | s<< 36 | s << 38 | s << 31 | s << 15 | s << 6;
        knight[22] = s << 5 | s << 12  | s << 28 | s<< 37 | s << 39 | s << 7;
        knight[23] = s << 6 | s << 13  | s << 29 | s<< 38;
        knight[24] = s << 9 | s << 18  | s << 34 | s<< 41;
        knight[25] = s << 8 | s << 40  | s << 42 | s<< 35 | s << 19 | s << 10;
        knight[26] = s << 9 | s << 16  | s << 32 | s<< 41 | s << 43 | s << 36 | s << 20 |s << 11;
        knight[27] = s << 10 | s << 17  | s << 33 | s<< 42 | s << 44 | s << 37 | s << 21 |s << 12;
        knight[28] = s << 11 | s << 18  | s << 24 | s<< 43 | s << 45 | s << 38 | s << 33 |s << 13;
        knight[29] = s << 12 | s << 19  | s << 25 | s<< 44 | s << 46 | s << 39 | s << 34 |s << 14;
        knight[30] = s << 13 | s << 20  | s << 36 | s<< 45 | s << 47 | s << 15;
        knight[31] = s << 14 | s << 21  | s << 37 | s<< 46 ;
        knight[32] = s << 17 | s << 49  | s << 42 | s<< 26;
        knight[33] = s << 16 | s << 48  | s << 50 | s<< 43 | s << 27 | s << 18;
        knight[34] = s << 17 | s << 24  | s << 40 | s<< 49 | s << 51 | s << 44 | s << 28 |s << 19;
        knight[35] = s << 18 | s << 25  | s << 41 | s<< 50 | s << 52 | s << 45 | s << 29 |s << 20;
        knight[36] = s << 19 | s << 26  | s << 42 | s<< 51 | s << 53 | s << 46 | s << 30 |s << 21;
        knight[37] = s << 20 | s << 27  | s << 43 | s<< 52 | s << 54 | s << 47 | s << 31 |s << 22;
        knight[38] = s << 21 | s << 28 | s << 44 | s<< 53 | s << 55 | s << 23;
        knight[39] = s << 22 | s << 29 | s << 45 | s<< 54;
        knight[40] = s << 57 | s << 50 | s << 34 | s<< 25;
        knight[41] = s << 24 | s << 56 | s << 58 | s<< 51 | s << 35 | s << 26 | s << 24;
        knight[42] = s << 25 | s << 32 | s << 48 | s<< 57 | s << 59 | s << 52 | s << 36 | s << 27;
        knight[43] = s << 26 | s << 33 | s << 49 | s<< 58 | s << 60 | s << 53 | s << 37 | s << 28;
        knight[44] = s << 27 | s << 34 | s << 50 | s<< 59 | s << 61 | s << 54 | s << 38 | s << 29;
        knight[45] = s << 28 | s << 35 | s << 51 | s<< 60 | s << 62 | s << 55 | s << 39 | s << 30;
        knight[46] = s << 29 | s << 36 | s << 52 | s<< 61 | s << 63 | s << 31;
        knight[47] = s << 30 | s << 37 | s << 53 | s<< 62;
        knight[48] = s << 58 | s << 42 | s << 33;
        knight[49] = s << 32 | s << 59 | s << 43 | s<< 34;
        knight[50] = s << 33 | s << 40 | s << 56 | s<< 60 | s << 44 | s << 35;
        knight[51] = s << 34 | s << 41 | s << 57 | s<< 61 | s << 45 | s << 36;
        knight[52] = s << 35 | s << 42 | s << 36 | s<< 58 | s << 62 | s << 46 | s << 37;
        knight[53] = s << 36 | s << 43 | s << 59 | s<< 63 | s << 47 | s << 38;
        knight[54] = s << 37 | s << 44 | s << 60 | s<< 39;
        knight[55] = s << 38 | s << 45 | 61;
        knight[56] = s << 41 | s << 50;
        knight[57] = s << 40 | s << 42 | s << 51;
        knight[58] = s << 48 | s << 41 | s << 43 | s<< 52;
        knight[59] = s << 49 | s << 42 | s << 44 | s<< 54;
        knight[60] = s << 50 | s << 43 | s << 45 | s<< 55;
        knight[61] = s << 51 | s << 44 | s << 46;
        knight[62] = s << 52 | s << 45 | s << 47;
        knight[63] = s << 53 | s << 46;
    }
    
    uint64_t generate(Board * board, int piecePos){
        int piece = board->fields[piecePos];
         uint64_t s = 1;
        switch(piece){
            case W_ROOK:
            {
                uint64_t r =  M42::rook_attacks(piecePos, board->all);
                r = r & ~board->w_all;
                return r;
            }
                
            case W_KNIGHT:
            {
                return knight[piecePos] & (board->empty | board->b_all);
            }
                
            case W_BISHOP:
            {
                uint64_t r =  M42::bishop_attacks(piecePos, board->all);
                r = r & ~board->w_all;
                return r;
            }
                
            case W_QUEEN:
            {
                uint64_t r =  M42::rook_attacks(piecePos, board->all);
                r =  r | M42::bishop_attacks(piecePos, board->all);
                r = r & ~board->w_all;
                return r;
            }
                
            case W_KING:
            {
                uint64_t r =  M42::king_attacks(piecePos);
                r = r & ~board->w_all;
                return r;
            }
                
            case W_PAWN:
            {
                uint64_t r = (w_prawnMoves[piecePos] & board->empty) | (w_prawnCatch[piecePos]  & board->b_all);
                if(board->b_enPasse > 0){
                    if(board->b_enPasse==32 && piecePos==33){
                        r = r | s << 40;
                    }
                    if(board->b_enPasse==33 && piecePos==32){
                        r = r | s << 41;
                    }
                    if(board->b_enPasse==33 && piecePos==34){
                        r = r | s << 41;
                    }
                    if(board->b_enPasse==34 && piecePos==33){
                        r = r | s << 42;
                    }
                    if(board->b_enPasse==34 && piecePos==35){
                        r = r | s << 42;
                    }
                    if(board->b_enPasse==35 && piecePos==34){
                        r = r | s << 43;
                    }
                    if(board->b_enPasse==35 && piecePos==36){
                        r = r | s << 43;
                    }
                    if(board->b_enPasse==36 && piecePos==35){
                        r = r | s << 44;
                    }
                    if(board->b_enPasse==36 && piecePos==37){
                        r = r | s << 44;
                    }
                    if(board->b_enPasse==37 && piecePos==36){
                        r = r | s << 45;
                    }
                    if(board->b_enPasse==37 && piecePos==38){
                        r = r | s << 45;
                    }
                    if(board->b_enPasse==38 && piecePos==37){
                        r = r | s << 46;
                    }
                    if(board->b_enPasse==38 && piecePos==39){
                        r = r | s << 46;
                    }
                    if(board->b_enPasse==39 && piecePos==38){
                        r = r | s << 47;
                    }
                }
                return r;
            }
                
            case B_ROOK:
            {
                uint64_t r =  M42::rook_attacks(piecePos, board->all);
                r = r & ~board->b_all;
                return r;
            }
                
            case B_KNIGHT:
            {
                return knight[piecePos] & (board->empty | board->w_all);
            }

            case B_BISHOP:
            {
                uint64_t r =  M42::bishop_attacks(piecePos, board->all);
                r = r & ~board->b_all;
                return r;
            }
                
            case B_QUEEN:
            {
                uint64_t r =  M42::bishop_attacks(piecePos, board->all);
                r =  r | M42::rook_attacks(piecePos, board->all);
                r = r & ~board->b_all;
                return r;
            }
                
            case B_KING:
            {
                uint64_t r =  M42::king_attacks(piecePos);
                r = r & ~board->b_all;
                return r;
            }
                
            case B_PAWN:
            {
                uint64_t r = b_prawnMoves[piecePos] & board->empty | (b_prawnCatch[piecePos]  & board->w_all);
                if(board->w_enPasse > 0){
                    if(board->w_enPasse==24 && piecePos==25){
                        r = r | s << 16;
                    }
                    if(board->w_enPasse==25 && piecePos==24){
                        r = r | s << 17;
                    }
                    if(board->w_enPasse==25 && piecePos==26){
                        r = r | s << 17;
                    }
                    if(board->w_enPasse==26 && piecePos==25){
                        r = r | s << 18;
                    }
                    if(board->w_enPasse==26 && piecePos==27){
                        r = r | s << 18;
                    }
                    if(board->w_enPasse==27 && piecePos==26){
                        r = r | s << 19;
                    }
                    if(board->w_enPasse==27 && piecePos==28){
                        r = r | s << 19;
                    }
                    if(board->w_enPasse==28 && piecePos==27){
                        r = r | s << 20;
                    }
                    if(board->w_enPasse==28 && piecePos==29){
                        r = r | s << 20;
                    }
                    if(board->w_enPasse==29 && piecePos==28){
                        r = r | s << 21;
                    }
                    if(board->w_enPasse==29 && piecePos==30){
                        r = r | s << 21;
                    }
                    if(board->w_enPasse==30 && piecePos==29){
                        r = r | s << 22;
                    }
                    if(board->w_enPasse==30 && piecePos==31){
                        r = r | s << 22;
                    }
                    if(board->w_enPasse==31 && piecePos==30){
                        r = r | s << 23;
                    }
                }
                return r;
            }
        }
        return 0;
    }
    
    vector<int> convertToPositions(uint64_t bitboard){
        uint64_t s = 1;
        vector<int> v;
        for(int i=0;i < 64;i++){
            if( (s << i) &  bitboard){
                v.push_back(i);
            }
        }
        return v;
    }
    
private:
};
