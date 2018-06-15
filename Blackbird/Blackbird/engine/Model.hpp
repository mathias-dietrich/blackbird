//
//  Model.hpp
//  Blackbird
//
//  Created by Mathias Dietrich on 6/14/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <string>
#include "Const.h"
#include "Board.h"

using namespace std;

class Model {
    
public:
    
    bool isFlipped = false;
    
    int selField = -1;
    
    bool hasLoaded = false;
    bool whiteToMove = true;
    
    Board *board;
    
    int selFields [64] ;
    
    void startPos(){
        for(int i=0;i < 64;i++){
            selFields[i] = EMPTY;
        }

        board = new Board();
        
        board->fields[0] = W_ROOK;
        board->fields[1] = W_KNIGHT;
        board->fields[2] = W_BISHOP;
        board->fields[3] = W_QUEEN;
        board->fields[4] = W_KING;
        board->fields[5] = W_BISHOP;
        board->fields[6] = W_KNIGHT;
        board->fields[7] = W_ROOK;
        
        board->fields[8] = W_PAWN;
        board->fields[9] = W_PAWN;
        board->fields[10] = W_PAWN;
        board->fields[11] = W_PAWN;
        board->fields[12] = W_PAWN;
        board->fields[13] = W_PAWN;
        board->fields[14] = W_PAWN;
        board->fields[15] = W_PAWN;
        
        board->fields[63] = B_ROOK;
        board->fields[62] = B_KNIGHT;
        board->fields[61] = B_BISHOP;
        board->fields[60] = B_KING;
        board->fields[59] = B_QUEEN;
        board->fields[58] = B_BISHOP;
        board->fields[57] = B_KNIGHT;
        board->fields[56] = B_ROOK;
        
        board->fields[55] = B_PAWN;
        board->fields[54] = B_PAWN;
        board->fields[53] = B_PAWN;
        board->fields[52] = B_PAWN;
        board->fields[51] = B_PAWN;
        board->fields[50] = B_PAWN;
        board->fields[49] = B_PAWN;
        board->fields[48] = B_PAWN;
        
        board->calcBitboards();
    }

private:
   
    
};

