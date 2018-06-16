//
//  Board.h
//  Blackbird
//
//  Created by Mathias Dietrich on 6/14/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

#pragma once

#include <string>
#include <vector>
#include "Const.h"
#include "Helper.hpp"
#include "Board.hpp"

using namespace std;

class Board{
    
public:
    
    Board * parent;
    vector<Board *> childen;
    
    Board(){
        for(int i=0;i < 64;i++){
           fields[i] = EMPTY;
        }
    }
    
    bool isInCheck(bool white);
    
    void startPos(){
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

        w_casteL = true;
        w_casteS = true;
        b_casteL = true;
        b_casteS = true;
        
        w_enPasse = 0;
        b_enPasse = 0;
        
        rule50 = 0;
        
        calcBitboards();
    }
    
    bool w_casteL;
    bool w_casteS;
    bool b_casteL;
    bool b_casteS;
    int w_enPasse = 0;
    int b_enPasse = 0;
    
    int fields [64];
    int rule50 = 0;
    
    uint64_t  w_rook;
    uint64_t  w_knight;
    uint64_t  w_bishop;
    uint64_t  w_queen;
    uint64_t  w_king;
    uint64_t  w_pawn;
    
    uint64_t  b_rook;
    uint64_t  b_knight;
    uint64_t  b_bishop;
    uint64_t  b_queen;
    uint64_t  b_king;
    uint64_t  b_pawn;
    
    uint64_t  w_all;
    uint64_t  b_all;
    uint64_t  all;
    uint64_t  empty;
    
    void calcBitboards(){
        w_rook = 0;
        w_knight = 0;
        w_bishop = 0;
        w_queen = 0;
        w_king = 0;
        w_pawn = 0;
        
        b_rook= 0;
        b_knight = 0;
        b_bishop = 0;
        b_queen = 0;
        b_king = 0;
        b_pawn = 0;
        const uint64_t s = 1;
        for(int i=0; i < 64; i++){
            switch(fields[i]){
                case W_ROOK:
                    w_rook = w_rook | s << i;
                    break;
                    
                case W_KNIGHT:
                    w_knight = w_knight | s << i;
                    break;
                    
                case W_BISHOP:
                    w_bishop = w_bishop | s << i;
                    break;
                    
                case W_QUEEN:
                    w_queen = w_queen | s << i;
                    break;
                    
                case W_KING:
                    w_king = w_king | s << i;
                    break;
                    
                case W_PAWN:
                    w_pawn = w_pawn | s << i;
                    break;
                    
                case B_ROOK:
                    b_rook = b_rook | s << i;
                    break;
                    
                case B_KNIGHT:
                    b_knight = b_knight | s << i;
                    break;
                    
                case B_BISHOP:
                    b_bishop = b_bishop | s << i;
                    break;
                    
                case B_QUEEN:
                    b_queen = b_queen | s << i;
                    break;
                    
                case B_KING:
                    b_king = b_king | s << i;
                    break;
                    
                case B_PAWN:
                    b_pawn = b_pawn | s << i;
                    break;
            }
        }
        
        w_all = w_rook | w_knight | w_bishop | w_queen | w_king | w_pawn;
        b_all = b_rook | b_knight | b_bishop | b_queen | b_king | b_pawn;
        
        empty = ~(w_all | b_all);
        all = ~empty;
        
        printAll();
    }
    
    /*
     Moving a Piece
     */
    void move(int from, int to){
         int figure = fields[from];
         if(figure==W_PAWN && to-8 == b_enPasse){
            fields[to-8] = EMPTY;
         }
         if(figure==B_PAWN && to+8 == w_enPasse){
            fields[to+8] = EMPTY;
         }
         fields[to] = figure;
         fields[from] = EMPTY;
        
        // castling
        if(figure == W_KING){
            if(from == 4 && to == 6){
                fields[7] = EMPTY;
                fields[5] = W_ROOK;
            }
            if(from == 4 && to == 2){
                fields[0] = EMPTY;
                fields[3] = W_ROOK;
            }
            w_casteL = false;
            w_casteS = false;
        }
        if(figure == B_KING){
            if(from == 60 && to == 62){
                fields[63] = EMPTY;
                fields[61] = B_ROOK;
            }
            if(from == 60 && to == 58){
                fields[56] = EMPTY;
                fields[59] = B_ROOK;
            }
            b_casteL = false;
            b_casteS = false;
        }
        if(figure == W_ROOK && from == 0) {
            w_casteL = false;
        }
        if(figure == W_ROOK && from == 7) {
            w_casteS = false;
        }
        if(figure == B_ROOK && from == 56) {
            b_casteL = false;
        }
           if(figure == B_ROOK && from == 63) {
            b_casteS = false;
        }
        
        // recalc
         calcBitboards();
        
        // en passe
         w_enPasse = 0;
         b_enPasse = 0;
         if(figure==W_PAWN && (to - from == 16)){
             w_enPasse = to;
         }
         if(figure==B_PAWN && (to-from == -16)){
             b_enPasse = to;
         }
    }
    
    void printAll(){
        Helper *helper = new Helper();
        cout << "w_rook" << endl;
        helper->printBitboard(w_rook);
        
        cout << "w_knight" << endl;
        helper->printBitboard(w_knight);
        
        cout << "w_bishop" << endl;
        helper->printBitboard(w_bishop);
        
        cout << "w_queen" << endl;
        helper->printBitboard(w_queen);
        
        cout << "w_king" << endl;
        helper->printBitboard(w_king);
        
        cout << "w_pawn" << endl;
        helper->printBitboard(w_pawn);
        
        cout << "b_rook" << endl;
        helper->printBitboard(b_rook);
        
        cout << "b_knight" << endl;
        helper->printBitboard(b_knight);
        
        cout << "b_bishop" << endl;
        helper->printBitboard(b_bishop);
        
        cout << "b_queen" << endl;
        helper->printBitboard(b_queen);
        
        cout << "b_king" << endl;
        helper->printBitboard(b_king);
        
        cout << "b_pawn" << endl;
        helper->printBitboard(b_pawn);
        
        cout << "w_all" << endl;
        helper->printBitboard(w_all);
        
        cout << "b_all" << endl;
        helper->printBitboard(b_all);
        
        cout << "empty" << endl;
        helper->printBitboard(empty);
        
        delete helper;
    }
    
    Board * copy(){
        Board *c = new Board();
        for(int i =0 ; i < 64;i++){
            c->fields[i] = fields[i];
        }
        c->w_rook = w_rook;
        c->w_rook = w_rook;
        c->w_knight = w_knight;
        c->w_bishop = w_bishop;
        c->w_queen = w_queen;
        c->w_king = w_king;
        c->w_pawn = w_pawn;
        
        c->b_rook = b_rook;
        c->b_knight = b_knight;
        c->b_bishop = b_bishop;
        c->b_queen = b_queen;
        c->b_king = b_king;
        c->b_pawn = b_pawn;
        return c;
    }
    
    string getFen(){
        return "";
    }
    
    // 50 Rule
    
    // Castling

};

