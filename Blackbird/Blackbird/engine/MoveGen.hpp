//
//  MoveGen.hpp
//  Blackbird
//
//  Created by Mathias Dietrich on 6/15/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

#include "Const.h"
#include "Helper.hpp"
#include "Board.hpp"

using namespace std;

class MoveGen{
public:
    
    uint64_t w_prawnMoves[64];
    uint64_t b_prawnMoves[64];
    
    uint64_t w_prawnCatch[64];
    uint64_t b_prawnCatch[64];
    
    MoveGen(){
        
        // Pawn Move
        uint64_t s = 1;
        for(int i=0;i<64;i++){
            w_prawnMoves[i] = 0;
            b_prawnMoves[i] = 0;
            w_prawnCatch[i] = 0;
            b_prawnCatch[i] = 0;
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
        b_prawnCatch[30] = s << 22 | s << 24;
        b_prawnCatch[29] = s << 21 | s << 23;
        b_prawnCatch[28] = s << 20 | s << 22;
        b_prawnCatch[27] = s << 19 | s << 21;
        b_prawnCatch[26] = s << 18 | s << 20;
        b_prawnCatch[25] = s << 17 | s << 19;
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
    }
    
    uint64_t generate(Board * board, int piecePos){
        int piece = board->fields[piecePos];
        
        switch(piece){
            case W_ROOK:
                break;
                
            case W_KNIGHT:
                break;
                
            case W_BISHOP:
                break;
                
            case W_QUEEN:
                break;
                
            case W_KING:
                break;
                
            case W_PAWN:
                return (w_prawnMoves[piecePos] & board->empty) | (w_prawnCatch[piecePos]  & board->b_all);
                
            case B_ROOK:
                break;
                
            case B_KNIGHT:
                break;
                
            case B_BISHOP:
                break;
                
            case B_QUEEN:
                break;
                
            case B_KING:
                break;
                
            case B_PAWN:
                return b_prawnMoves[piecePos] & board->empty | (b_prawnCatch[piecePos]  & board->w_all);
                break;
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
