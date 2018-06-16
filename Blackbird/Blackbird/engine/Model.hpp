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
#include "Move.hpp"

using namespace std;

class Model {
    
public:
    int moveNo = 1;
    bool debugMode = false;
    string debugMsg = "App Starts";
    string moveList = "new game";
    
    string w_timeBox = "White";
    string b_timeBox = "Black";
    
    vector<Move*> moves;
    Move * move;
    
    bool isFlipped = false;
    
    int selField = -1;
    
    bool hasLoaded = false;
    bool whiteToMove = true;
    
    Board *root;
    Board *board;
    
    int selFields [64] ;
    
    void startPos(){
        board = new Board();
        root = board;
        board->startPos();
        for(int i=0;i < 64;i++){
            selFields[i] = EMPTY;
        }
        moveNo = 1;
    }

private:
   
    
};

