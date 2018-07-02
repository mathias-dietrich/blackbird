//
//  Uci.hpp
//  Blackbird
//
//  Created by Mathias Dietrich on 6/28/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//
// http://wbec-ridderkerk.nl/html/UCIProtocol.html

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

class Uci {
    
public:
    
    Uci(){}
    
    string fenStr = "";
    int maxTime = 5000;
    int maxDepth = 3; // minimum 1 needs odd numnbers?
    bool isEmbedded = true;
    
    //  MinMax itself
    Analyzer *analyzer = new Analyzer();
    
    static void* staticFunction(void* p)
    {
        static_cast<Uci*>(p)->memberFunction();
        return NULL;
    }

    void memberFunction();
    
    bool listen(string cmd){
        
        analyzer->isEmbedded = isEmbedded;
        
        // split
        stringstream ss(cmd);
        string item;
        vector<string> tokens;
        while (getline(ss, item, ' ')) {
            tokens.push_back(item);
        }
        
        if(tokens.size() == 0){
            return true;
        }
        if(tokens.at(0) == "quit"){
            return false;
        }
        if(tokens.at(0) == "stop"){
            analyzer->stop();
            return true;
        }
        if(tokens.at(0) == "uci"){
            cout << "uci ok" << endl;
            return true;
        }
        if(tokens.at(0) == "position"){
            string fen = "";
            for(int i = 2; i < tokens.size(); i++){
                fen += tokens.at(i) + " ";
            }
            fenStr = fen;
        }
        
        if(tokens.at(0) == "go"){
            analyse();
        }
        return true;
    }
    
private:
    pthread_t threads[1];
    
    void analyse(){
        pthread_create(&threads[0], NULL,  staticFunction, this);
    }
};
