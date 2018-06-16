//
//  Engine.hpp
//  Blackbird
//
//  Created by Mathias Dietrich on 6/14/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <sstream>
#include "Model.hpp"
#include "MoveGen.hpp"

class Engine{
 
private:
    Engine(){

    }
    
    static  Engine * m_pInstance;
    
public:
    MoveGen *gen = new MoveGen();
    Model *model =  new Model();
    
    /*
     Move one move forward, called by UI
     */
    void move(int from, int to){
        
        // Create next Board
        Board *newBoard = model->board->copy();
        newBoard->boardId++;
       
        model->boardIndex++;
        model->boardMax = model->boardIndex;

        model->boards[model->boardIndex] = newBoard;
        model->board = newBoard;
        
        int figure = model->board->fields[from];
        model->board->move(from,to);
        
        // record the move
        if(model->board->whiteToMove){

           model->board->moveStr = pieceToLetter(figure) + fieldToLetter(from) + "-" + fieldToLetter(to);

            // castling
            if(figure == W_KING){
                if(from == 4 && to == 6){
                    model->board->moveStr = "O-O";
                }
                if(from == 4 && to == 2){
                    model->board->moveStr = "O-O-O";
                }
            }
           
        }else{
            model->board->moveStr = pieceToLetter(figure) + fieldToLetter(from) + "-" + fieldToLetter(to);
            
            // castling
            if(figure == B_KING){
                if(from == 60 && to == 62){
                    model->board->moveStr = "O-)";
                }
                if(from == 60 && to == 58){
                   model->board->moveStr = "O-O-O";
                }
            }
        }
        
        // rewrite the move list
        calcMoveList();

       // flip color
        model->board->whiteToMove = !model->board->whiteToMove;
        
        // Reset UI fields
        model->selField = -1;
    }
    
    void calcMoveList(){
        model->moveList = "";

        int moveId = 1;
        int isWhite = true;
        
        for (int i=1; i < model->boardMax +1; i++)
        {
            Board *board =  model->boards[i];
            
            if(isWhite){
                stringstream ss;
                ss << moveId;
                string intStr = ss.str();
                model->moveList += intStr + ". " + board->moveStr;
            }else{
                model->moveList += " " + board->moveStr + "\n";
            }
            isWhite = !isWhite;
        }
    }

    static Engine * Instance()
    {
        if (NULL == m_pInstance){  
            m_pInstance = new Engine;
        }
        return m_pInstance;
    }

    void startPos(){
        model->startPos();
    }
    
    void newWhite(){
         model->isFlipped = false;
         model->startPos();
    }
    
    void newBlack(){
         model->startPos();
         model->isFlipped = true;
    }
    
    void flip(){
        model->isFlipped =  !model->isFlipped ;
    }
    
    void backwards(){
        int index = model->boardIndex;
        if(index == 0){
            return;
        }
        index--;
        model->boardIndex = index;
        model->boardMax--;
        model->board = model->boards[index];
        model->board ->printAll();
        calcMoveList();
    }
    
    void forwards(){
        cout << "forwards" << endl;
    }
    
    void promoteQueen(){
         cout << "promoteQueen" << endl;
    }
    
    void promoteRook(){
         cout << "promoteRook" << endl;
    }
    
    void promoteKnight(){
         cout << "promoteKnight" << endl;
    }
    
    void promoteBishop(){
         cout << "promoteBishop" << endl;
    }
    
    void debugMode(){
        model->debugMode =  !model->debugMode;
    }
    
    void clearDebug(){
        model->debugMsg = "";
    }
    
    string fieldToLetter(int field){
        return string(1,char(49 + field / 8 )) + string(1,char(97 + field % 8));
    }
    
    string pieceToLetter(int piece){
        switch(piece){
            case W_PAWN:
            case B_PAWN:
                return "";
                
            case W_KING:
            case B_KING:
                return "K";
                
            case W_QUEEN:
            case B_QUEEN:
                return "Q";
                
            case W_ROOK:
            case B_ROOK:
                return "R";
                
            case W_BISHOP:
            case B_BISHOP:
                return "B";
                
            case W_KNIGHT:
            case B_KNIGHT:
                return "N";
        }
        return "";
    }
};

Engine * Engine::m_pInstance = NULL;

