//
//  Analyzer.hpp
//  Blackbird
//
//  Created by Mathias Dietrich on 6/29/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//
// https://gist.github.com/byanofsky/c8dd06cd1b1fb8d06a9dd695d07e403e

#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <cstdio>
#include <sstream>
#include <memory>
#include <stdexcept>
#include <array>
#include <unistd.h>
#include <sys/wait.h>
#include <fstream>

#include "Global.hpp"
#include "Helper.hpp"
#include "Board.hpp"
#include "m42.h"
#include "Observer.hpp"
#include "Fen.hpp"
#include "Eval.hpp"
#include "Ply.hpp"
#include "MoveGen.hpp"

using namespace std;

class Analyzer{
    
public:
    const string engineName = "Blackbird 1  by Mathias Dietrich";
    bool isEmbedded = false;
    int depth;
    int time;
    string fenStr;
    Board *board;
    bool isStop = false;
    Eval *eval = new Eval();
    MoveGen *moveGen = new MoveGen();
    int value;
    
    bool isDebug = true;
    
     Board *boardFinal;
    
    void stop(){
        isStop = true;
    }
    
    int evaluateBoard(Board * board){
        return eval->eval(board, board->whiteToMove);
    }
    
    
    void sortMoves(vector<Ply> * moves, bool randomize){
        
    }
    
    int minmax(int depth, Board * board, bool playerColor,int alpha ,int beta, bool isMaximizingPlayer){
   
         if (depth == 0) {
              boardFinal = board;
             return evaluateBoard(board);
            
         }
        
        // Recursive case: search possible movesb
        Ply bestMove;
        vector<Ply> possibleMoves = moveGen->generateAll(board);
        int count = 0;
        
        //Debug print moves
        if(isDebug){
            for(int i=0; i< possibleMoves.size(); i++){
                Ply p = possibleMoves.at(i);
                cout << "===========================" << endl;
                cout << count << endl;
                count++;
                p.printAll();
            }
        }
        
        // Sort
        sortMoves(&possibleMoves, true);
        
        // Set a default best move value
        int bestMoveValue = isMaximizingPlayer ? -100000 : 100000;
        
        // Search through all possible moves
        for (int i = 0; i < possibleMoves.size(); i++) {
            
            Ply move = possibleMoves.at(i);
            board->move(move);
            
            value = minmax(depth-1, board, playerColor, alpha, beta, !isMaximizingPlayer);
            cout << "value; " << value <<  " playerColor: " << playerColor <<  " alpha: "  << alpha <<  " beta: "  << beta << endl;
            
            if (isMaximizingPlayer) {
                // Look for moves that maximize position
                if (value > bestMoveValue) {
                    bestMoveValue = value;
                    bestMove = move;
                }
                 alpha = max(alpha, value);
            }else {
                // Look for moves that minimize position
                if (value < bestMoveValue) {
                    bestMoveValue = value;
                    bestMove = move;
                }
                beta = min(beta, value);
            }
            
            // undo move
            board->undoMove();
            
            // prune
            if (beta <= alpha) {
                cout << "Prune: alpha: " << alpha << " beta: " <<  beta << endl;
                break;
            }
        }
        return value;
    }
                
    void analyze(int depth, int time, string fenStr){
        isStop = false;
        this->depth = depth;
        this->time = time;
        this->fenStr = fenStr;
        this->board = fen->parse(fenStr);
        
        // Engine says Hello
        cout << engineName << endl;
        
        int alpha = -10000000;
        int beta = 10000000;
        
        // minmax
        int val = minmax(depth, this->board, board->whiteToMove, alpha, beta, true);
        cout << "==================================" << endl;
        cout << "best move eval: " << val << endl;
       
        boardFinal->printAll();
        
         cout << "==================================" << endl;
        // sorting
        
        // SSE
        
        /*
        Ply ply;
        if(isEngineWhite){
           // observer->makeMoveWhite(ply);
        }else{
           // observer->makeMoveBlack(ply);
        }
        */
    }
    
private:
     Fen *fen = new Fen();
};
