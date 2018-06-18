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

#include "Const.hpp"
#include "Helper.hpp"
#include "Board.hpp"
#include "m42.h"

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
                            sum += 100;
                            break;
                            
                        case W_ROOK:
                            sum += 500;
                            break;
                            
                        case W_BISHOP:
                            sum += 300;
                            break;
                            
                        case W_KNIGHT:
                            sum += 300;
                            break;
                            
                        case W_QUEEN:
                            sum += 900;
                            break;
                    }
                }
            }else{
                if(figure < 0){
                    switch(figure){
                        case B_PAWN:
                            sum += 100;
                            break;
                            
                        case B_ROOK:
                            sum += 500;
                            break;
                            
                        case B_BISHOP:
                            sum += 300;
                            break;
                            
                        case B_KNIGHT:
                            sum += 300;
                            break;
                            
                        case B_QUEEN:
                            sum += 900;
                            break;
                    }
                }
            }
        }
        return sum;
    }
};

