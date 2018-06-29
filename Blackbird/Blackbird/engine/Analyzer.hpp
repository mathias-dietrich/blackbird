//
//  Analyzer.hpp
//  Blackbird
//
//  Created by Mathias Dietrich on 6/29/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

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
#include <boost/process.hpp>
#include <boost/filesystem.hpp>
#include <boost/asio.hpp>
#include "Observer.hpp"

using namespace std;

class Analyzer{
    
public:
    void analyze(int depth, int time, string fen){
        
        bool isEngineWhite = true;
        
        // minmax
        
        // sorting
        
        // SSE
        
        Ply ply;
        if(isEngineWhite){
            observer->makeMoveWhite(ply);
        }else{
            observer->makeMoveBlack(ply);
        }
    }
};
