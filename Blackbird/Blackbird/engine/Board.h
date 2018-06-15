//
//  Board.h
//  Blackbird
//
//  Created by Mathias Dietrich on 6/14/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

#pragma once

#include <string>
#include "Const.h"

using namespace std;

class Board{
    
public:

    Board(){
        for(int i=0;i < 64;i++){
           fields[i] = EMPTY;
        }
    }
    int fields [64] ;
    
    uint64_t  w_rook;
    uint64_t  w_knight;
    uint64_t  w_bishop;
    uint64_t  w_queen;
    uint64_t  w_king;
    uint64_t  w_pawn;
    
    uint64_t  b_rook;
    uint64_t  b_knight;
    uint64_t  b_bishop;
    uint64_t  b_queen;
    uint64_t  b_king;
    uint64_t  b_pawn;
    
    void calcBitboards(){
        w_rook = 0;
        w_knight = 0;
        w_bishop = 0;
        w_queen = 0;
        w_king = 0;
        w_pawn = 0;
        
        b_rook= 0;
        b_knight = 0;
        b_bishop = 0;
        b_queen = 0;
        b_king = 0;
        b_pawn = 0;
        for(int i=0; i < 64; i++){
            switch(fields[i]){
                case W_ROOK:
                    w_rook = w_rook| 1 << i;
                    break;
                    
                case W_KNIGHT:
                    w_knight = w_knight | 1 << i;
                    break;
                    
                case W_BISHOP:
                    w_bishop = w_bishop | 1 << i;
                    break;
                    
                case W_QUEEN:
                    w_queen = w_queen | 1 << i;
                    break;
                    
                case W_KING:
                    w_king = w_king | 1 << i;
                    break;
                    
                case W_PAWN:
                    w_pawn = w_pawn | 1 << i;
                    break;
                    
                case B_ROOK:
                    b_rook = b_rook | 1 << i;
                    break;
                    
                case B_KNIGHT:
                    b_knight = b_knight | 1 << i;
                    break;
                    
                case B_BISHOP:
                    b_bishop = b_bishop | 1 << i;
                    break;
                    
                case B_QUEEN:
                    b_queen = b_queen | 1 << i;
                    break;
                    
                case B_KING:
                    b_king = b_king | 1 << i;
                    break;
                    
                case B_PAWN:
                    b_pawn = b_pawn | 1 << i;
                    break;
            }
        }
    }
    
    void move(int from, int to){
        // set fields
        
        // set bitboards
    }
    
    Board * copy(){
        Board *c = new Board();
        for(int i =0 ; i < 64;i++){
            c->fields[i] = fields[i];
        }
        c->w_rook = w_rook;
        c->w_rook = w_rook;
        c->w_knight = w_knight;
        c->w_bishop = w_bishop;
        c->w_queen = w_queen;
        c->w_king = w_king;
        c->w_pawn = w_pawn;
        
        c->b_rook = b_rook;
        c->b_knight = b_knight;
        c->b_bishop = b_bishop;
        c->b_queen = b_queen;
        c->b_king = b_king;
        c->b_pawn = b_pawn;
        return c;
    }
    
    string getFen(){
        return "";
    }
    
    // 50 Rule
    
    // Castling

};

