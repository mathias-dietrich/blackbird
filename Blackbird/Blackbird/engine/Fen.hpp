//
//  Fen.hpp
//  Blackbird
//
//  Created by Mathias Dietrich on 6/17/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

#include "Helper.hpp"
#include "Board.hpp"
#include "m42.h"

class Fen{
public:
    
    
    string parse(Board * board){
        string fen = "";
        int count = 0;
        
        for(int y=7; y>-1; y--){
            for(int x=0; x < 8; x++){
                
                int field = board->fields[x  + y * 8];
                
                if(field!=0 && count >0){
                    fen += std::to_string(count);
                    count = 0;
                }
                
                switch(field){
                        
                    case W_PAWN:
                        fen += "P";
                        break;
                        
                    case W_ROOK:
                        fen += "R";
                        break;
                        
                    case W_KNIGHT:
                        fen += "N";
                        break;
                        
                    case W_BISHOP:
                        fen += "B";
                        break;
                        
                    case W_QUEEN:
                        fen += "Q";
                        break;
                        
                    case W_KING:
                        fen += "K";
                        break;
                        
                    case B_PAWN:
                        fen += "p";
                        break;
                        
                    case B_ROOK:
                        fen += "r";
                        break;
                        
                    case B_KNIGHT:
                        fen += "n";
                        break;
                        
                    case B_BISHOP:
                        fen += "b";
                        break;
                        
                    case B_QUEEN:
                        fen += "q";
                        break;
                        
                    case B_KING:
                        fen += "k";
                        break;
                        
                    case 0:
                        count++;
                        break;
                }
            }
            if(y>-1 && count >0){
                fen += std::to_string(count);
                count = 0;
            }
            if(y>0){
                fen += "/";
            }
        }
        fen += " ";
        if(board->whiteToMove){
            fen += "w";
        }else{
            fen += "b";
        }
        fen += " ";
        if(!board->w_casteS  && !board->w_casteS && !board->b_casteS && !board->b_casteL){
            fen += "-";
        }
        if(board->w_casteS){
            fen += "K";
        }
        if(board->w_casteL){
            fen += "Q";
        }
        if(board->b_casteS){
            fen += "k";
        }
        if(board->b_casteL){
            fen += "q";
        }
        
        fen += " ";
        string temp("abcdefgh");
        stringstream ss;
        
        if(board->w_enPasse > 0){
            int r = (board->w_enPasse - 8) % 8;
            ss << temp.at(r) << "3";
            fen += ss.str();
        }else if(board->b_enPasse > 0){
            int r = (board->b_enPasse + 8) % 8;
            ss << temp.at(r) << "6";
            fen += ss.str();
        }else{
            fen += "-";
        }
        fen += " ";
        fen += std::to_string(board->rule50);
        fen += " ";
        fen += std::to_string(board->moveId);
        return fen;
    }
};
