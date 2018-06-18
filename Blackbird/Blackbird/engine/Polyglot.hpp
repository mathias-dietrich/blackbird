//
//  Polyglot.hpp
//  Blackbird
//
//  Created by Mathias Dietrich on 6/18/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

#ifndef Polyglot_hpp
#define Polyglot_hpp

#include <stdio.h>

#include <vector>
#include <iostream>
#include <sstream>
#include <string>

#include "pg_key.h"
#include "pg_show.h"
#include "Type.hpp"
#include "Fen.hpp"
#include "Ply.hpp"


using namespace std;

/*
 RandomPiece     (offset:   0, length: 768)
 RandomCastle    (offset: 768, length:   4)
 RandomEnPassant (offset: 772, length:   8)
 RandomTurn      (offset: 780, length:   1)
 
 key=piece^castle^enpassant^turn;
 offset_piece=64*kind_of_piece+8*row+file;
 
 black pawn    0
 white pawn    1
 black knight  2
 white knight  3
 black bishop  4
 white bishop  5
 black rook    6
 white rook    7
 black queen   8
 white queen   9
 black king   10
 white king   11
 
 offesets:
 white can castle short     0
 white can castle long      1
 black can castle short     2
 black can castle long      3
 
 bits                meaning
 ===================================
 0,1,2               to file
 3,4,5               to row
 6,7,8               from file
 9,10,11             from row
 12,13,14            promotion piece
 "promotion piece" is encoded as follows
 none       0
 knight     1
 bishop     2
 rook       3
 queen      4
 
 white short      e1h1
 white long       e1a1
 black short      e8h8
 black long       e8a8
 */

class Polyglot
{
public:
    
    U64 position;
    short int move;
    short int weight;
    unsigned int learn;
    
    Ply getBookMove(Board * board);
    string bookPath;
    
    
private:
    
};

#endif /* Polyglot_hpp */
