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

#include "Type.hpp"
#include "Helper.hpp"
#include "Board.hpp"
#include "m42.h"

class Fen{
public:
    
    Board * parse(string fen){
        Board *cboard = new Board();

        for(int i=0; i < 64; i++){
            cboard->fields[i] = 0;
        }
        
        int column = 0;
        int row = 7;
        
        bool parseEnd = false;
        for(int i=0; i < fen.length(); i++){
            
            if(parseEnd){
                string end = "";
                for(; i < fen.length(); i++){
                    end +=fen.at(i);
                }
                
                std::stringstream os(end); // a standard stringstream which parses 's'
                std::string temp;
                
                int state = 0;
                while (os >> temp) {
                    
                    switch(state){
                            
                        case 0:
                            if(temp =="w"){
                                cboard->whiteToMove = true;
                            }else{
                                cboard->whiteToMove = false;
                            }
                            state++;
                            break;
                            
                        case 1:
                            cboard->b_casteS = false;
                            cboard->w_casteS = false;
                            cboard->w_casteL = false;
                            cboard->b_casteL = false;
                            if (temp.find("K") != std::string::npos) {
                                cboard->w_casteS = true;
                            }
                            if (temp.find("Q") != std::string::npos) {
                                cboard->w_casteL = true;
                            }
                            if (temp.find("k") != std::string::npos) {
                                cboard->b_casteS = true;
                            }
                            if (temp.find("q") != std::string::npos) {
                                cboard->b_casteL = true;
                            }
                            state++;
                            break;
                            
                        case 2:
                            if(temp.find("3") !=std::string::npos)
                            {
                                int r = temp[0]-64;
                                cboard->w_enPasse = MASK[27+r];
                            }
                            if(temp.find("4")!=std::string::npos)
                            {
                                int r = temp[0]-64;
                                cboard->w_enPasse = MASK[43+r];
                            }
                            state++;
                            break;
                            
                        case 3:
                            int num;
                            std::istringstream(temp) >> num;
                            cboard->rule50 = num;
                            state++;
                            break;
                            
                        case 4:
                            int num2;
                            std::istringstream(temp) >> num2;
                          //  cboard->fullmoves = (num2-1) ;
                            if(!cboard->whiteToMove){
                                //cboard->fullmoves++;
                            }
                            state++;
                    }
                }
                cboard->calcBitboards();
                return cboard;
            }
            
            switch(fen.at(i)){
                    
                case ' ':
                    parseEnd = true;
                    break;
                    
                case '/':
                    row--;
                    column = 0;
                    break;
                    
                case '1':
                    column++;
                    break;
                    
                case '2':
                    column+=2;
                    break;
                    
                case '3':
                    column+=3;
                    break;
                    
                case '4':
                    column+=4;
                    break;
                    
                case '5':
                    column+=5;
                    break;
                    
                case '6':
                    column+=6;
                    break;
                    
                case '7':
                    column+=7;
                    break;
                    
                case '8':
                    column+=8;
                    break;
                    
                case 'r':
                    cboard->fields[row*8+column] = B_ROOK;
                    column++;
                    break;
                    
                case 'n':
                    cboard->fields[row*8+column] = B_KNIGHT;
                    column++;
                    break;
                    
                case 'b':
                    cboard->fields[row*8+column] = B_BISHOP;
                    column++;
                    break;
                    
                case 'q':
                    cboard->fields[row*8+column] = B_QUEEN;
                    column++;
                    break;
                    
                case 'k':
                    cboard->fields[row*8+column] = B_KING;
                    column++;
                    break;
                    
                case 'p':
                    cboard->fields[row*8+column] = B_PAWN;
                    column++;
                    break;
                    
                case 'R':
                    cboard->fields[row*8+column] = W_ROOK;
                    column++;
                    break;
                    
                case 'N':
                    cboard->fields[row*8+column] = W_KNIGHT;
                    column++;
                    break;
                    
                case 'B':
                    cboard->fields[row*8+column] = W_BISHOP;
                    column++;
                    break;
                    
                case 'Q':
                    cboard->fields[row*8+column] = W_QUEEN;
                    column++;
                    break;
                    
                case 'K':
                    cboard->fields[row*8+column] = W_KING;
                    column++;
                    break;
                    
                case 'P':
                    cboard->fields[row*8+column] = W_PAWN;
                    column++;
                    break;
            }
        }
        cboard->calcBitboards();
        return cboard;
    }
    
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
