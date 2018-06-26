//
//  Transposition.hpp
//  Blackbird
//
//  Created by Mathias Dietrich on 6/25/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

#pragma once

#include <string>
#include <vector>
#include <stdlib.h>

#include "Type.hpp"
#include "pg_key.h"
#include "Board.hpp"
#include "Fen.hpp"
#include "Zobrist.hpp"
#include "Ply.hpp"

using namespace std;

enum EvalType{HASH_EXACT,HASH_BETA,HASH_ALPHA};

struct TPTable{
    uint64_t key;
    string fen;
    int depth;
    int eval;
    EvalType evalType;
    Ply * bestMove;
};

class Transposition{
    
    public:

    void add(Board * board, int depth, int eval, EvalType evalType, Ply *ply){
        TPTable table;
        uint64_t key = zobrist->hash(board);
        table.key = key;
        table.depth = depth;
        table.eval = eval;
        table.evalType = evalType;
        table.bestMove = ply;
        map[key] = table;
    }
    
    TPTable get(uint64_t key){
        if (map.find(key) == map.end()){
            TPTable table;
            return table;
        }
        return map[key];
    }
    
private:
     std::unordered_map< uint64_t, TPTable> map;
    Zobrist *zobrist = new Zobrist();
    

};
