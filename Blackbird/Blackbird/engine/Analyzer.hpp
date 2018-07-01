//
//  Analyzer.hpp
//  Blackbird
//
//  Created by Mathias Dietrich on 6/29/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//
// https://gist.github.com/byanofsky/c8dd06cd1b1fb8d06a9dd695d07e403e

// https://chessprogramming.wikispaces.com/Alpha-Beta

// https://github.com/official-stockfish/Stockfish/blob/master/src/search.cpp

// https://chessprogramming.wikispaces.com/Principal%20Variation%20Search

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
    bool isEmbedded = true;
    int depth;
    int time;
    string fenStr;
    Board *board;
    bool isStop = false;
    int value;
    bool isDebug = false;
    Board *boardBest;
    int bestScore = 0;

    void stop(){
        isStop = true;
    }

    // Sorting moves - for now only by score
    vector<Ply> sortMoves(vector<Ply>  moves, bool randomize){
        vector<Ply> sorted;
        int pos = 0;
        bool sorting = true;
        Ply bestMove;
        while(sorting)
        {
            if(moves.at(0).isWhite)
            {
                int score = INT_MIN;
                for(int i=0; i < moves.size();i++){
                    Ply ply = moves.at(i);
                    if(ply.score > score){
                        bestMove = ply;
                        score = ply.score ;
                        pos = i;
                    }
                }
                sorted.push_back(bestMove);
                moves.erase(moves.begin()+pos);
                if(moves.size() < 1){
                    sorting = false;
                }
            }else{
                int score = INT_MAX;
                for(int i=0; i < moves.size();i++){
                    Ply ply = moves.at(i);
                    if(ply.score < score){
                        bestMove = ply;
                        score = ply.score ;
                        pos = i;
                    }
                }
                sorted.push_back(bestMove);
                moves.erase(moves.begin()+pos);
                if(moves.size() < 1){
                     sorting = false;
                }
            }
        }
        return sorted;
    }
    
    // TODO implent and add SEE  Static Exchange Evaluation
    int quiesce(Board * board, int alpha, int beta, bool whiteToMove ){
        int score = eval->eval(board, board->whiteToMove);
        if(board->whiteToMove == whiteToMove && score > bestScore){
            boardBest = board;
            bestScore = score;
            boardBest->score = score;
            boardBest->ply.score = score;
            cout << "quiesce white from: " << board->ply.from << " to: " << board->ply.to << " score: " <<  board->ply.score << endl;
        }
        if(!board->whiteToMove == whiteToMove && score < bestScore){
            boardBest = board;
            bestScore = score;
            boardBest->ply.score = score;
            boardBest->score = score;
            cout << "quiesce black from: " << board->ply.from << " to: " << board->ply.to << " score: " <<  board->ply.score << endl;
        }
        return score;
    }
    
    int pvSearch(Board * board, int alpha, int beta, int depth, bool whiteToMove ) {
        
        // return at depth 0 - also TODO at check mate
        if( depth == 0 ) {
            return quiesce(board, alpha, beta, whiteToMove);
        }
        bool bSearchPv = true;

        // Generate Moves
         vector<Ply> moves = moveGen->generateAll(board);
        
        // eval the moves for the sort
        for(int i=0; i< moves.size();i++){
            
            Board *b = board->copy();
            b->move(moves.at(i));
            b->whiteToMove = ! b->whiteToMove;
            moves.at(i).score = eval->eval(b, b->whiteToMove);
            delete b;
        }
        
        // Sort Moves
        moves = sortMoves(moves, false);

        // Try next move
        for ( int i=0;i<moves.size();i++)  {
            Board *b = board->copy();
            b->move(moves.at(i));
            b->whiteToMove = ! b->whiteToMove;
            int score;
            if ( bSearchPv ) {
                 score = -pvSearch(b, -beta, -alpha, depth - 1,whiteToMove);
            } else {
                 score = -zwSearch(b, -alpha, depth - 1,whiteToMove);
                if ( score > alpha ) // in fail-soft ... && score < beta ) is common
                    score = -pvSearch(b, -beta, -alpha, depth - 1,whiteToMove); // re-search
            }
            delete b;
            if( score >= beta )
                return beta;   // fail-hard beta-cutoff
            if( score > alpha ) {
                alpha = score; // alpha acts like max in MiniMax
                bSearchPv = false;   // *1)
            }
        }
        return alpha;
    }
    
    // fail-hard zero window search, returns either beta-1 or beta
    int zwSearch(Board *board, int beta, int depth,bool whiteToMove  ) {
        // alpha == beta - 1
        // this is either a cut- or all-node
        if( depth == 0 ) return quiesce(board, beta-1, beta,whiteToMove);
        vector<Ply> moves = moveGen->generateAll(board);
         for ( int i=0;i<moves.size();i++)  {
            Board *b = board->copy();
            b->move(moves.at(i));
            b->whiteToMove = ! b->whiteToMove;
            int score = -zwSearch(b, 1-beta, depth - 1,whiteToMove);
             delete b;
            if( score >= beta )
                return beta;   // fail-hard beta-cutoff
        }
        return beta-1; // fail-hard, return alpha
    }

    void analyze(int depth, int time, string fenStr){
        isStop = false;
        this->depth = depth;
        this->time = time;
        this->fenStr = fenStr;
        this->board = fen->parse(fenStr);
        
        // Engine says Hello
        cout << engineName << endl;
        
        int alpha = INT_MIN;
        int beta = INT_MAX;
        if(board->whiteToMove){
            bestScore = INT_MIN;
        }else{
            bestScore = INT_MAX;
        }
        
        // minmax
        int val = pvSearch(this->board, alpha, beta, depth, board->whiteToMove);
        if(isEmbedded)
        {
            cout << "best move eval: " << val << endl;
            
            if( board->whiteToMove){
                observer->makeMoveWhite(boardBest->ply);
            }else{
                observer->makeMoveBlack(boardBest->ply);
            }
        }
    }
    
private:
    Eval *eval = new Eval();
    MoveGen *moveGen = new MoveGen();
    Fen *fen = new Fen();
};
