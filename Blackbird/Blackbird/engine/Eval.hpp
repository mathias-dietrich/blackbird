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
    int eval(Board * board, bool isWhite){
        
        int sum = 0;
        // First eval on material value
        for(int i=0; i < 64 ;i ++){
            int figure = board->fields[i];
            if(isWhite){
                if(figure > 0){
                    switch(figure){
                        case W_PAWN:
                            sum += VAL_PAWN;
                            break;
                            
                        case W_ROOK:
                            sum += VAL_ROOK;
                            break;
                            
                        case W_BISHOP:
                            sum += VAL_BISHOP;
                            break;
                            
                        case W_KNIGHT:
                            sum += VAL_KNIGHT;
                            break;
                            
                        case W_QUEEN:
                            sum += VAL_QUEEN;
                            break;
                            
                        case W_KING:
                            sum += VAL_KING;
                            break;
                    }
                }
            }else{
                if(figure < 0){
                    switch(figure){
                        case B_PAWN:
                            sum += VAL_PAWN;
                            break;
                            
                        case B_ROOK:
                            sum += VAL_ROOK;
                            break;
                            
                        case B_BISHOP:
                            sum += VAL_BISHOP;
                            break;
                            
                        case B_KNIGHT:
                            sum += VAL_KNIGHT;
                            break;
                            
                        case B_QUEEN:
                            sum += VAL_QUEEN;
                            break;
                            
                        case B_KING:
                            sum += VAL_KING;
                            break;
                    }
                }
            }
        }
        return sum;
    }
};

