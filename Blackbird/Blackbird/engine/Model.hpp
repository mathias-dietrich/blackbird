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
#include "Board.hpp"
#include <chrono>
#include "Type.hpp"

using namespace std;

class Model {
    
public:
     bool paused = false;
    WINSTATE winstate = PNG;
    
    bool enginePlaysWhite = true;
    bool enginePlaysBlack = true;
    
    void clearSelection(){
        for(int i=0;i< 64;i++){
            selFields[i] = EMPTY;
        }
        selField = -1;
    }
    
   
    bool useBook = true;
    
    string fenStr = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    string resourceRoot = "";
    
    std::chrono::time_point<std::chrono::system_clock> startTime ;
    
    string engineNameBlack = "Fruit";
    string engineNameWhite = "Komodo";
    string bookName = "Komodo";
    
    int w_time;
    int b_time;
    
    bool rule50CaptureOrPawn;
    int rule50Count = 0;
    
    int promotionField = 0;
    bool isPromotion = false;
    bool isMate = false;
    bool isDraw = false;
    int boardIndex = 0;
    int boardMax = 0;
    
    int w_eval = 0;
    int b_eval = 0;
   
    bool debugMode = false;
    
    string debugMsg = "App Starts";
    string moveList = "";
    string engineList = "";
    
    string w_timeBox = "White";
    string b_timeBox = "Black";
    
    bool isFlipped = false;
    bool hasLoaded = false;
    
    Board * boards[2000];
    Board * board;
    
    int selFields [64] ;
    int selField = -1;
    int lastField = -1;
    
    void startPos(){
        fenStr = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        w_time = 0;
        b_time = 0;
        isDraw = false;
        isPromotion = false;
        debugMsg = "New Game";
        moveList = "";
        isMate = false;
        board = new Board();
        boards[0] = board;
        board->startPos();
        clearSelection();
        boardIndex = 0;
        lastField = -1;
    }

private:
   
    
};

