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
    bool isWhite;
    int score;
    int from;
    int to;
    bool isCapture;
    bool isCheck;
    bool isCheckMate;
    PIECE piece;
    PIECE capturedPiece;
    bool isLegal;
    int captureValue;
    CASTLE castle;
    int promotion;
    bool isPromotion;
    bool enpassW;
    bool enpassB;
} Ply;

#endif /* Ply_h */
