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
#include "Const.h"
#include "Board.hpp"

using namespace std;

class Model {
    
public:
    int boardIndex = 0;
    int boardMax = 0;
   
    bool debugMode = false;
    string debugMsg = "App Starts";
    string moveList = "";
    
    string w_timeBox = "White";
    string b_timeBox = "Black";
    
    bool isFlipped = false;
    
    int selField = -1;
    
    bool hasLoaded = false;
    
    Board * boards[2000];
    Board * board;
    
    int selFields [64] ;
    
    void startPos(){
        board = new Board();
        boards[0] = board;
        board->startPos();
        for(int i=0;i < 64;i++){
            selFields[i] = EMPTY;
        }
        boardIndex = 0;
    }

private:
   
    
};

