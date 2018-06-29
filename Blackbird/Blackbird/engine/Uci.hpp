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
#include <iostream>
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

class Uci{
    
public:
    
    string fenStr = "";
    int maxTime = 5000;
    int maxDepth = 32;
    
    static void* staticFunction(void* p)
    {
        static_cast<Uci*>(p)->memberFunction();
        return NULL;
    }
    
    void memberFunction();
    
    void listen(string cmd){
        
        // split
        
        
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
