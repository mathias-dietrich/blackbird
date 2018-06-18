//
//  Polyglot.cpp
//  Blackbird
//
//  Created by Mathias Dietrich on 6/18/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

#include "Polyglot.hpp"

Ply Polyglot::getBookMove(Board * board){
    
    Ply ply;
    ply.from = -1;
    ply.castle = NONE;
    ply.isCheck = false;
    ply.isCapture = false;
    ply.enpassB = false;
    ply.enpassW = false;
    ply.isPromotion = false;
    ply.isWhite = board->whiteToMove;
    ply.isLegal = false;

    
    pg_key *keyParser = new pg_key();
    Fen *parser = new Fen();
    pg_show *book = new pg_show();
    
    // get FEN
    string fen = parser->parse(board);
    
    // Get Polyglot Hash Key
    U64 hash = keyParser->findHash(fen);
    cout << "hash " << hash << endl;
    
    string moveText = book->readBook(hash, bookPath);
    
    // Clean up
    delete keyParser;
    delete parser;
    delete book;
    
    cout << "moveText " << moveText << endl;
    if(moveText == "ERR"){
        cout << "Book failing";
        return ply;
        
    }
    
    // parse move
    if(moveText.length() > 4){
        cout << "Book failing";
    }
    
    int from = moveText[0]-97 + (moveText[1]-49) * 8;
    int to = moveText[2]-97 + (moveText[3]-49) * 8;
    
    if(moveText == "e8g8" && board->b_casteS){
        ply.castle = CBK;
    }
    if(moveText == "e8c8" && board->b_casteL){
        ply.castle = CBQ;
    }
    if(moveText == "e1g1" && board->w_casteS){
        ply.castle = CWK;
    }
    if(moveText == "e1c1" && board->w_casteL){
        ply.castle = CWQ;
    }
    
    // return Ply
    ply.from = from;
    ply.to = to;
    ply.isLegal = true;
    
    if(board->fields[to] !=0 ){
        ply.isCapture = true;
        ply.capturedPiece = board->fields[to];
    }
    
    return ply;
}

