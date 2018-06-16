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
        int figure = model->board->fields[from];
        model->board->move(from,to);
        
        // record the move
        if(model->whiteToMove){
            Move * move = new Move();
            move->w_from = from;
            move->w_to = to;
            move->w_figure = figure;
            move->w_move = "white move ";
            move->w_move = pieceToLetter(figure) + fieldToLetter(from) + "-" + fieldToLetter(to);
            move->id = model->moveNo;
            model->move = move;
            model->moves.push_back(move);
            
            // castling
            if(figure == W_KING){
                if(from == 4 && to == 6){
                    move->w_move = "O-O";
                }
                if(from == 4 && to == 2){
                    move->w_move = "O-O-O";
                }
            }
        }else{
            model->move->b_from = from;
            model->move->b_to = to;
            model->move->b_figure = figure;
            model->move->b_move = pieceToLetter(figure) + fieldToLetter(from) + "-" + fieldToLetter(to);
            model->moveNo++;
            
            // castling
            if(figure == B_KING){
                if(from == 60 && to == 62){
                    model->move->b_move = "O-)";
                }
                if(from == 60 && to == 58){
                    model->move->b_move = "O-O-O";
                }
            }
        }
        
        // calculate move list
        model->moveList = "";
        vector<Move*>::iterator it;
        for(it = model->moves.begin(); it != model->moves.end(); it++)    {
            Move *move =  *it ;
            stringstream ss;
            ss << move->id;
            string intStr = ss.str();
            string strId = string(intStr);
            
            model->moveList += strId + ". " +move->w_move + " " + move->b_move + "\n";
        }

        model->whiteToMove = ! model->whiteToMove;
        model->selField = -1;
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
        model->whiteToMove = true;
    }
    
    void newBlack(){
         model->startPos();
        model->isFlipped = true;
        model->whiteToMove = false;
    }
    
    void flip(){
        model->isFlipped =  !model->isFlipped ;
    }
    
    void backwards(){
        cout << "backwards" << endl;
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

