//
//  Uci.hpp
//  Blackbird
//
//  Created by Mathias Dietrich on 6/28/18.
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
#include "Analyzer.hpp"

using namespace std;

class Uci{
    
public:
    
    string fenStr = "";
    int maxTime = 5000;
    int maxDepth = 32;
    Analyzer *analyzer = new Analyzer();
    
    static void* staticFunction(void* p)
    {
        static_cast<Uci*>(p)->memberFunction();
        return NULL;
    }
    
    void memberFunction();
    
    void listen(string cmd){
        
        // split
        stringstream ss(cmd);
        string item;
        vector<string> tokens;
        while (getline(ss, item, ' ')) {
            tokens.push_back(item);
        }
        
        if(tokens.at(0) == "position"){
            
            string fen = "";
             cout  << endl;
            for(int i = 2; i < tokens.size(); i++){
                fen += tokens.at(i) + " ";
            }
            cout << fen << endl;
            
            // https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring    trim
        }
        
        if(tokens.at(0) == "go"){
            
        }
        
        
        // position
        
        // go
        
        cout << cmd << endl;
    }
    
    void analyse(string fen){
         fenStr = fen;
         pthread_create(&threads[0], NULL,  staticFunction, this);
    }
    
private:
    pthread_t threads[1];
};
