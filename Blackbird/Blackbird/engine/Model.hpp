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
    
    bool isFlipped = false;
    
    int selField = -1;
    
    bool hasLoaded = false;
    bool whiteToMove = true;
    
    Board *board;
    
    int selFields [64] ;
    
    void startPos(){
        board = new Board();
        board->startPos();
        for(int i=0;i < 64;i++){
            selFields[i] = EMPTY;
        }
    }

private:
   
    
};

