//
//  Model.hpp
//  Blackbird
//
//  Created by Mathias Dietrich on 6/14/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include <stdio.h>
#include <string>
#include "Const.h"

using namespace std;

class Model {
    
public:
    
    int selField = -1;
    
    bool hasLoaded = false;
    bool whiteToMove = true;
    
    int fields [64] ;
    int selFields [64] ;
    
    void startPos(){
        
        for(int i=0;i < 64;i++){
            fields[i] = EMPTY;
            selFields[i] = EMPTY;
        }
       // selFields[12] = SELECTED;
       // selFields[20] = OPTION;
       // selFields[28] = OPTION;
        
        fields[0] = W_ROOK;
        fields[1] = W_KNIGHT;
        fields[2] = W_BISHOP;
        fields[3] = W_QUEEN;
        fields[4] = W_KING;
        fields[5] = W_BISHOP;
        fields[6] = W_KNIGHT;
        fields[7] = W_ROOK;
        
        fields[8] = W_PAWN;
        fields[9] = W_PAWN;
        fields[10] = W_PAWN;
        fields[11] = W_PAWN;
        fields[12] = W_PAWN;
        fields[13] = W_PAWN;
        fields[14] = W_PAWN;
        fields[15] = W_PAWN;
        
        fields[63] = B_ROOK;
        fields[62] = B_KNIGHT;
        fields[61] = B_BISHOP;
        fields[60] = B_KING;
        fields[59] = B_QUEEN;
        fields[58] = B_BISHOP;
        fields[57] = B_KNIGHT;
        fields[56] = B_ROOK;
        
        fields[55] = B_PAWN;
        fields[54] = B_PAWN;
        fields[53] = B_PAWN;
        fields[52] = B_PAWN;
        fields[51] = B_PAWN;
        fields[50] = B_PAWN;
        fields[49] = B_PAWN;
        fields[48] = B_PAWN;
    }

    
private:
   
    
};


#endif /* Model_hpp */
