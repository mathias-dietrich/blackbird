//
//  Eval.hpp
//  Blackbird
//
//  Created by Mathias Dietrich on 6/16/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

#include "Helper.hpp"
#include "Board.hpp"
#include "m42.h"
#include "Type.hpp"

class Eval{

public:
    int eval(Board * board, bool isWhiteToMove){
        int sum = 0;
        
        int material = evalMaterial(board, isWhiteToMove);
        sum += material;
        
        //prefer Pawn moves
        if(board->boardId > 0){
            if(board->fields[board->ply.to] == B_PAWN  && !isWhiteToMove){
                sum += 10;
            }
            if(board->fields[board->ply.to] == W_PAWN  && isWhiteToMove){
                sum -= 10;
            }
            
            if(board->ply.to==27 ||  board->ply.to==28 ||  board->ply.to==35 ||  board->ply.to==36 ){
                if(isWhiteToMove)
                {
                    sum -= 10;
                }else{
                    sum += 10;
                }
            }
        }
        board->score = sum;
        return sum;
    }
    
    int evalMaterial(Board * board, bool isWhite){
        int sum = 0;
        int materialWhite = 0;
        int materialBlack = 0;
        
        for(int i=0; i < 64 ;i ++){
            switch(board->fields[i]){
                case EMPTY:
                    break;
                    
                case W_PAWN:
                    sum += VAL_PAWN;
                    materialWhite += VAL_PAWN;
                    break;
                    
                case W_ROOK:
                    sum += VAL_ROOK;
                    materialWhite += VAL_ROOK;
                    break;
                    
                case W_BISHOP:
                    sum += VAL_BISHOP;
                    materialWhite += VAL_BISHOP;
                    break;
                    
                case W_KNIGHT:
                    sum += VAL_KNIGHT;
                    materialWhite += VAL_KNIGHT;
                    break;
                    
                case W_QUEEN:
                    sum += VAL_QUEEN;
                    materialWhite += VAL_QUEEN;
                    break;
                    
                case W_KING:
                    sum += VAL_KING;
                    materialWhite += VAL_KING;
                    break;
                    
                case B_PAWN:
                    sum -= VAL_PAWN;
                    materialBlack += VAL_PAWN;
                    break;
                    
                case B_ROOK:
                    sum -= VAL_ROOK;
                    materialBlack += VAL_ROOK;
                    break;
                    
                case B_BISHOP:
                    sum -= VAL_BISHOP;
                    materialBlack += VAL_BISHOP;
                    break;
                    
                case B_KNIGHT:
                    sum -= VAL_KNIGHT;
                    materialBlack += VAL_KNIGHT;
                    break;
                    
                case B_QUEEN:
                    sum -= VAL_QUEEN;
                    materialBlack += VAL_QUEEN;
                    break;
                    
                case B_KING:
                    sum -= VAL_KING;
                    materialBlack += VAL_KING;
                    break;
            }
        }
        board->materialWhite = materialWhite;
        board->materialBlack = materialBlack;
        return sum;
    }
};

