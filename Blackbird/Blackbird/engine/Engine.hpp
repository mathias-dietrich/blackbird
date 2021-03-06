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
#include <string>
#include <iostream>

#include "Model.hpp"
#include "MoveGen.hpp"
#include "Eval.hpp"
#include "EngineWrapper.hpp"
#include "Fen.hpp"
#include "Observer.hpp"
#include "Polyglot.hpp"
#include "Zobrist.hpp"
#include "Transposition.hpp"

using namespace std;

class Engine : Observer{
 
public:
    Model *model = new Model();
    MoveGen *gen = new MoveGen();
    
    void makeMoveWhite(Ply ply){
        if(!model->pausedWhite){
            move(ply);
        }
    }
    
    void makeMoveBlack(Ply ply){
        if(!model->pausedBlack){
            move(ply);
        }
    }
    
    void logEngine(string msg){
        model->engineList = msg +  model->engineList;
    }
    
    void setupEngines(){
        engineWhite->isEngineWhite = true;
        engineBlack->isEngineWhite = false;
        engineWhite->setup(model->resourceRoot + "/"+ model->engineNameWhite);
        engineBlack->setup(model->resourceRoot + "/"+ model->engineNameBlack);
    }
    
    void updateEngineWhite(){
        engineWhite->setup(model->resourceRoot + "/"+ model->engineNameWhite);
    }
    
    void updateEngineBlack(){
        engineBlack->setup(model->resourceRoot + "/"+ model->engineNameBlack);
    }
    
    /*
     Move one move forward, called by UI
     */
    void move(Ply ply){
        model->lastField = ply.to;
        Board *newBoard = model->board->copy();
        newBoard->score = ply.score;
       
        model->boardIndex++;
        model->boardMax = model->boardIndex;

        model->boards[model->boardIndex] = newBoard;
        model->board = newBoard;
        
        // record the move
        int figure = model->board->fields[ply.from];
        
        if(ply.isPromotion){
            figure = ply.promotion;
        }
        
        if(model->board->whiteToMove){

            model->rule50CaptureOrPawn = false;
            if(figure == W_PAWN){
                model->rule50CaptureOrPawn = true;
            }
            if(model->board->fields[ply.to] != EMPTY){ // capture
                 model->board->moveStr =  pieceToLetter(figure) + fieldToLetter(ply.from) +  "x" + fieldToLetter(ply.to);
                 model->rule50CaptureOrPawn = true;
            }else if(ply.isPromotion){
                 model->board->moveStr =  fieldToLetter(ply.from) +   "-" + fieldToLetter(ply.to) + pieceToPromortionLetter(ply.promotion);
            }else{
                 model->board->moveStr = pieceToLetter(figure) + fieldToLetter(ply.from) +   "-" + fieldToLetter(ply.to);
            }
          
            // castling
            if(figure == W_KING){
                if(ply.from == 4 && ply.to == 6){
                    model->board->moveStr = "O-O";
                }
                if(ply.from == 4 && ply.to == 2){
                    model->board->moveStr = "O-O-O";
                }
            }
            
            // promotion in manual play
            if(figure == W_PAWN && ply.to > 55){
                model->isPromotion = true;
                model->promotionField = ply.to;
            }
        }else{ // black to move
            if(figure == B_PAWN){
                model->rule50CaptureOrPawn = true;
            }
            if(model->board->fields[ply.to] != EMPTY){ // capture
                model->board->moveStr = pieceToLetter(figure) + fieldToLetter(ply.from) +  "x" + fieldToLetter(ply.to);
                model->rule50CaptureOrPawn = true;
            }else{
                model->board->moveStr = pieceToLetter(figure) +  fieldToLetter(ply.from) + "-" + fieldToLetter(ply.to);
            }
            
            // castling
            if(figure == B_KING){
                if(ply.from == 60 && ply.to == 62){
                    model->board->moveStr = "O-O";
                }
                if(ply.from == 60 && ply.to == 58){
                   model->board->moveStr = "O-O-O";
                }
            }
            // promotion in manual play
            if(figure == B_PAWN && ply.to < 8){
                model->isPromotion = true;
                model->promotionField = ply.to;
            }
            if(!model->rule50CaptureOrPawn){
                model->rule50Count++;
            }
        }
        
        // make the move
        model->board->move(ply);
        
        // get Zobrist Hash
        cout << "Zobrist Hash: " << zobrist->hash(model->board) << endl;
        
        // shortcut here if manual play
        if(model->isPromotion ){
            return;
        }
        
        // check if King in check
        bool isKingInCheck = gen->inCheck(model->board, model->board->whiteToMove);
        if(isKingInCheck){
            model->board->moveStr += "+";
            
            // Mate ?
            if(gen->isMate(model->board, model->board->whiteToMove)){
                model->isMate = true;
                 model->board->moveStr += "+";
            }
        }
        // rewrite the move list
        calcMoveList();

        model->clearSelection();
        
        model->fenStr = fenparser->parse( model->board);
        
        // if engine is black
        if(model->board->whiteToMove ){
            if(!model->pausedWhite){
                pthread_create(&threads[0], NULL,  newThreadWhite, this);
            }
        }else{
            if(!model->pausedBlack){
                pthread_create(&threads[0], NULL,  newThreadBlack, this);
            }
        }
    }
    
    static void* newThreadBlack(void* p)
    {
        static_cast<Engine*>(p)->makeEngineMoveBlack();
        return NULL;
    }
    
    static void* newThreadWhite(void* p)
    {
        static_cast<Engine*>(p)->makeEngineMoveWhite();
        return NULL;
    }
    
    void makeEngineMoveBlack(){
        // can we handle in the book
        if(model->useBook){
            polyglot->bookPath = model->resourceRoot + "/" + model->bookName + ".bin";
            Ply ply = polyglot->getBookMove(model->board);
            if(ply.isLegal){
                move(ply);
                return;
            }
        }
        
        string fenStr = fenparser->parse(model->board);
        model->fenStr = fenStr;
        engineBlack->toEngine( ("position fen " + fenStr + " \n").c_str() );
        string time = to_string(model->engineTimeoutBlack);
        engineBlack->toEngine(("go movetime " + time +  " \n").c_str() );
    }
    
    void makeEngineMoveWhite(){
        // can we handle in the book
        if(model->useBook){
            polyglot->bookPath = model->resourceRoot + "/" + model->bookName + ".bin";
            Ply ply = polyglot->getBookMove(model->board);
            if(ply.isLegal){
                move(ply);
                return;
            }
        }
        
        string fenStr = fenparser->parse(model->board);
        model->fenStr = fenStr;
        engineWhite->toEngine( ("position fen " + fenStr + " \n").c_str() );
        string time = to_string(model->engineTimeoutWhite);
        engineWhite->toEngine(("go movetime " + time + " \n").c_str() );
    }
    
    void handlePromotion(int figure){
        
        if(model->isPromotion){
            if(model->board->whiteToMove){
                figure = -1 * figure;
            }
            model->board->fields[model->promotionField] = figure;
            string letter = pieceToLetter(figure);
            model->board->moveStr += letter;
            
            // check if King in check
            bool isKingInCheck = gen->inCheck(model->board, !model->board->whiteToMove);
            if(isKingInCheck){
                model->board->moveStr += "+";
                
                // Mate ?
                if(gen->isMate(model->board, !model->board->whiteToMove)){
                    model->board->moveStr += "+";
                }
            }
            // rewrite the move list
            calcMoveList();

            // Reset UI fields
            model->selField = -1;
            
            model->isPromotion = false;
        }
    }
    
    /*
     Calulcate the move list and formats for reading
     */
    void calcMoveList(){
        model->moveList = "";

        int moveId = 1;
        int isWhite = true;
        
        for (int i=1; i < model->boardMax +1; i++)
        {
            Board *board =  model->boards[i];
            
            if(isWhite){
                stringstream ss;
                ss << moveId << ".";
                if(model->boardIndex == i){
                    ss << " ==> ";
                }
                string intStr = ss.str();
                model->moveList += intStr + board->moveStr;
            }else{
                model->moveList += " ";
                
                if(model->boardIndex == i){
                    model->moveList += " ==> ";
                }
                model->moveList += board->moveStr + "\n";
                moveId++;
            }
            isWhite = !isWhite;
        }
    }
    
    // Singleton
    static Engine * Instance()
    {
        if (NULL == m_pInstance){  
            m_pInstance = new Engine;
        }
        return m_pInstance;
    }

    // Methods - Button Handler
    void startPos(){
        model->startPos();
        eval->eval(model->board, model->board->whiteToMove);
    }
    
    void newWhite(){
         model->isFlipped = false;
         model->startPos();
        if(!model->pausedWhite){
            makeEngineMoveWhite();
        }
    }
    
    void newBlack(){
         model->startPos();
         model->isFlipped = true;
        if(!model->pausedBlack){
            makeEngineMoveBlack();
        }
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
        model->board = model->boards[index];
        calcMoveList();
        model->pausedWhite = true;
        model->pausedBlack = true;
    }
    
    void forward(){
        int index = model->boardIndex;
        if(index == model->boardMax){
            return;
        }
        index++;
        model->boardIndex = index;
        model->board = model->boards[index];
        calcMoveList();
        model->pausedWhite = true;
        model->pausedBlack = true;
    }
    
    void promoteQueen(){
        handlePromotion(W_QUEEN);
    }
    
    void promoteRook(){
         handlePromotion(W_ROOK);
    }
    
    void promoteKnight(){
         handlePromotion(W_KNIGHT);
    }
    
    void promoteBishop(){
         handlePromotion(W_BISHOP);
    }
    
    void debugMode(){
        model->debugMode =  !model->debugMode;
    }
    
    void clearDebug(){
        model->debugMsg = "";
        model->engineList = "";
    }
    
    void draw(){
        model->board->moveStr += " 1/2-1/2";
        calcMoveList();
        model->isDraw = true;
    }
    
    string fieldToLetter(int field){
        return string(1,char(97 + field % 8)) + string(1,char(49 + field / 8));
    }
    
    // Helper
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
    
    string pieceToPromortionLetter(int piece){
        switch(piece){
            case W_QUEEN:
            case B_QUEEN:
                return "q";
                
            case W_ROOK:
            case B_ROOK:
                return "r";
                
            case W_BISHOP:
            case B_BISHOP:
                return "b";
                
            case W_KNIGHT:
            case B_KNIGHT:
                return "n";
        }
        return "";
    }
    
    void setFen(string fen){
        Board *b = fenparser->parse(fen);
        eval->eval(b, b->whiteToMove);
        model->fenStr = fen;
        model->board = b;
        model->boards[0] = b;
        model->boardIndex = 0;
        model->boardMax = 1;
        model->pausedWhite = true;
        model->pausedBlack = true;
    }
    
private:
    Engine(){
        observer = this;
    }
    
    static  Engine * m_pInstance;
    pthread_t threads[1];
    Transposition  *transposition = new Transposition();
    Zobrist *zobrist = new Zobrist();
    Fen *fenparser = new Fen();
    Eval *eval = new Eval();
   
   
    Polyglot *polyglot = new Polyglot();
    
    EngineWrapper  *engineWhite = new EngineWrapper();
    EngineWrapper  *engineBlack = new EngineWrapper();
};

// Instance singleton
Engine * Engine::m_pInstance = NULL;

