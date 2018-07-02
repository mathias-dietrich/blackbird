//
//  Ply.hpp
//  Blackbird
//
//  Created by Mathias Dietrich on 6/18/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

#ifndef Ply_h
#define Ply_h

#include <vector>
#include <iostream>
#include <sstream>
#include <string>

#include "Type.hpp"

using namespace std;

typedef struct
{
    void printAll(){
        cout << "====== PLY =========="  << endl;
        cout << "from " << from << endl;
        cout << "to " << to << endl;
        cout << "isCapture " << isCapture << endl;
        cout << "isCheck " << isCheck << endl;
        cout << "piece " << piece << endl;
        cout << "capturedPiece " << capturedPiece << endl;
        cout << "isLegal " << isLegal << endl;
        cout << "captureValue " << captureValue << endl;
        cout << "castle " << castle << endl;
        cout << "promotion " << promotion << endl;
        cout << "enpassW " << enpassW << endl;
        cout << "enpassB " << enpassB << endl;
        cout << "isWhite " << isWhite << endl;
        cout << "score " << score << endl;
    }
    bool isWhite = true;
    int score = 0;
    int from = -1;
    int to = -1;
    bool isCapture = false;
    bool isCheck = false;
    bool isCheckMate = false;
    PIECE piece = 0;
    PIECE capturedPiece = 0;
    bool isLegal = false;
    int captureValue = 0;
    CASTLE castle = NONE;
    int promotion = 0;
    bool isPromotion = false;
    bool enpassW = -1;
    bool enpassB = -1;
} Ply;

#endif /* Ply_h */
