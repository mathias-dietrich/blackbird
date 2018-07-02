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

#include "Type.hpp"

#include "Helper.hpp"
#include "Ply.hpp"

using namespace std;

class Board{
    
public:
    vector<Board *> history;
    int boardId = 0;
    Ply ply;
    vector<Ply> plies;
    string moveStr = "";
    int moveId = 1;
    string comment = "";
    
    int score = 0;
    int materialWhite = 82000;
    int materialBlack = 82000;
    
    Board(){
        for(int i=0;i < 64;i++){
           fields[i] = EMPTY;
        }
    }
    
    void startPos(){
        moveStr = "";
        moveId = 0;
        boardId = 0;
        
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
    
    bool whiteToMove = true;
    
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
    }
    
    
    void undoMove(){
        Board *b = history.back();
        set(b);
        history.pop_back();
    }
    
    void set(Board * b){
        all =  b->all;
        empty = b->empty;
        
        b_all = b->b_all;
        w_all = b->w_all;
        
        b_rook = b->b_rook;
        w_rook = b->w_rook;
        
        b_knight = b->b_knight;
        w_knight = b->w_knight;
        
        b_bishop = b->b_bishop;
        w_bishop = b->w_bishop;
        
        b_queen = b->b_queen;
        w_queen = b->w_queen;
        
        b_king = b->b_king;
        w_king = b->w_king;
        
        b_pawn = b->b_pawn;
        w_pawn = b->w_pawn;
        
        w_casteL = b->w_casteL;
        w_casteS = b->w_casteS;
        
        b_casteL = b->b_casteL;
        b_casteS = b->b_casteS;
        
        boardId = b->boardId;
        moveId = b->moveId;
        moveStr = b->moveStr;
        
        w_enPasse = b->w_enPasse;
        b_enPasse = b->b_enPasse;
        
        for(int i=0; i < 64; i++){
            fields[i] = b->fields[i];
        }
        comment = b->comment;
        rule50 = b->rule50;
        whiteToMove = b->whiteToMove;
        
        moveId = b->moveId;
        boardId = b->boardId;
        
        ply = b->ply;
        moveStr = b->moveStr;
        score = b->score;
    }
    
    /*
     Moving a Piece
     */
    void move(Ply ply){

        //copy
        history.push_back(this->copy());
        
        plies.push_back(ply);
        
        //
        this->ply = ply;
        int from = ply.from;
        int to = ply.to;
        
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
        whiteToMove = !whiteToMove;
        boardId++;
    }
    
    void printNice(){
        cout << "   A B C D E F G H " << endl << endl;
        for(int r=7;r >-1;r--){
            cout << r+1 << "  ";
            for(int c=0;c < 8;c++){
                int pos = r * 8 + c;
                int piece = fields[pos];
                switch(piece){
                    case EMPTY:
                        cout << "- ";
                        break;
                        
                    case W_PAWN:
                        cout << "P ";
                        break;
                        
                    case W_ROOK:
                        cout << "R ";
                        break;
                        
                    case W_KNIGHT:
                        cout << "N ";
                        break;
                        
                    case W_BISHOP:
                        cout << "B ";
                        break;
                        
                    case W_QUEEN:
                        cout << "Q ";
                        break;
                        
                    case W_KING:
                        cout << "K ";
                        break;
                        
                    case B_PAWN:
                        cout << "p ";
                        break;
                        
                    case B_ROOK:
                        cout << "r ";
                        break;
                        
                    case B_KNIGHT:
                        cout << "n ";
                        break;
                        
                    case B_BISHOP:
                        cout << "b ";
                        break;
                        
                    case B_QUEEN:
                        cout << "q ";
                        break;
                        
                    case B_KING:
                        cout << "k ";
                        break;
                }
            }
            cout << " " << r+1 << endl;
        }
        cout << endl << "   A B C D E F G H " << endl;
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
        
         printNice();
        
        cout << "w_enPasse " << w_enPasse << endl;
        cout << "b_enPasse " << b_enPasse << endl;
        cout << "w_casteL " << w_casteL << endl;
        cout << "w_casteS " << w_casteS << endl;
        cout << "b_casteL " << b_casteL << endl;
        cout << "b_casteS " << b_casteS << endl;
        cout << "rule50 " << rule50 << endl;
        cout << "whiteToMove " << whiteToMove << endl;
        cout << "boardId " << boardId << endl;

        ply.printAll();
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
        
        c->w_all = w_all;
        c->b_all = b_all;
        c->all = all;
        c->empty = empty;
        
        c->w_casteL = w_casteL;
        c->w_casteS = w_casteS;
        c->b_casteL = b_casteL;
        c->b_casteS = b_casteS;
        c->rule50 = rule50;
        c->w_enPasse = w_enPasse;
        c->b_enPasse = b_enPasse;
    
        c->rule50 = rule50;
        c->whiteToMove = whiteToMove;
        c->boardId = boardId;
        c->moveId = moveId;
        c->moveStr = moveStr;
        c->ply = ply;
        c->score = score;
        c->materialWhite = materialWhite;
        c->materialBlack = materialWhite;
        
        for(int i=0; i < plies.size();i++){
            c->plies.push_back(ply);
        }
       
        return c;
    }
};

