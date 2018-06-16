//
//  Board.cpp
//  Blackbird
//
//  Created by Mathias Dietrich on 6/15/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

#include <stdio.h>
#include "Board.hpp"

bool Board::isInCheck(bool white){
    
   
    // get all figures of the color
    for(int i=0;i < 64;i++){
        int figure = fields[i];
        if(white && figure < 1){
            continue;
        }
        if(!white && figure > -1){
            continue;
        }
        
    }
    return false;
}
