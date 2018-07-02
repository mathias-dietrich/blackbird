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
    bool debugMode = false;
    bool runClock = false;
    bool pausedWhite = true;
    bool pausedBlack = false;
    bool useBook = false;
    bool rule50CaptureOrPawn;
    bool isPromotion = false;
    bool isMate = false;
    bool isDraw = false;
    bool isFlipped = false;
    bool hasLoaded = false;
    
    int engineTimeoutWhite = 10000;
    int engineTimeoutBlack = 10000;
    int w_time;
    int b_time;
    int rule50Count = 0;
    int boardIndex = 0;
    int boardMax = 0;
    int selFields [64] ;
    int selField = -1;
    int lastField = -1;
    int promotionField = 0;

    string engineNameWhite = "User";
    string engineNameBlack = "Blackbird";
    //string engineNameBlack = "User";
    string bookName = "No Opening Book";
    string fenStr = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    string resourceRoot = "";
    string debugMsg = "App Starts";
    string moveList = "";
    string engineList = "";
    string w_timeBox = "White";
    string b_timeBox = "Black";

    Board * boards[2000];
    Board * board;
    
    WINSTATE winstate = PNG;
    
    std::chrono::time_point<std::chrono::system_clock> startTime ;

    void clearSelection(){
        for(int i=0;i< 64;i++){
            selFields[i] = EMPTY;
        }
        selField = -1;
    }
    
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
        runClock = false;
    }

private:
    
};

