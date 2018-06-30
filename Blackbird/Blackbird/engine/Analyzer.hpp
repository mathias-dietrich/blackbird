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
    
    void stop(){
        isStop = true;
    }
    
    int evaluateBoard(Board * board){
        return eval->eval(board, board->whiteToMove);
    }
    
    int minmax(int depth, Board * board, bool playerColor,int alpha ,int beta, bool isMaximizingPlayer){
   
         if (depth == 0) {
             return evaluateBoard(board);
         }
        
        Ply bestMove;
        vector<Ply> possibleMoves = moveGen->generateAll(board);
        int count = 0;
        for(int i=0; i< possibleMoves.size(); i++){
            Ply p = possibleMoves.at(i);
            cout << "===========================" << endl;
            cout << count << endl;
            count++;
            p.printAll();
        }
    /*
         // Recursive case: search possible movesb
         var bestMove = null; // best move not set yet
         var possibleMoves = game.moves();
     
         // Set random order for possible moves
         possibleMoves.sort(function(a, b){return 0.5 - Math.random()});
     
         // Set a default best move value
         var bestMoveValue = isMaximizingPlayer ? Number.NEGATIVE_INFINITY: Number.POSITIVE_INFINITY;
     
         // Search through all possible moves
         for (var i = 0; i < possibleMoves.length; i++) {
             var move = possibleMoves[i];
              
             // Make the move, but undo before exiting loop
             game.move(move);
              
              
             // Recursively get the value from this move
             value = calcBestMove(depth-1, game, playerColor, alpha, beta, !isMaximizingPlayer)[0];
              
             // Log the value of this move
             console.log(isMaximizingPlayer ? 'Max: ' : 'Min: ', depth, move, value,
             bestMove, bestMoveValue);
             
             if (isMaximizingPlayer) {
                 // Look for moves that maximize position
                 if (value > bestMoveValue) {
                 bestMoveValue = value;
                 bestMove = move;
             }
             alpha = Math.max(alpha, value);
              
             } else {
                 // Look for moves that minimize position
                 if (value < bestMoveValue) {
                 bestMoveValue = value;
                 bestMove = move;
             }
             beta = Math.min(beta, value);
         }
              
         // Undo previous move
         game.undo();
              
         // Check for alpha beta pruning
         if (beta <= alpha) {
              console.log('Prune', alpha, beta);
              break;
         }
         */
             
        return 0;
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
        minmax(depth, this->board, board->whiteToMove, alpha, beta, true);
       
        
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
