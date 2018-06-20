//
//  EngineWrapper.hpp
//  Blackbird
//
//  Created by Mathias Dietrich on 6/16/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//
// https://www.erack.de/download/pipe-fork.c
// https://www.chessprogramming.net/uci-protocol-capturing-user-input/

// http://wbec-ridderkerk.nl/html/UCIProtocol.html

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
namespace bp = ::boost::process;

#define PIPE_READ 0
#define PIPE_WRITE 1

class EngineWrapper {
public:

    bool isEngineWhite;
    static void* staticFunction(void* p)
    {
        static_cast<EngineWrapper*>(p)->memberFunction();
        return NULL;
    }
    
    int aStdinPipe[2];
    int aStdoutPipe[2];
    int nChild;
    char nChar;
    int nResult;
    bp::opstream instream;
    bp::ipstream outstream;
    
    void setup(string engine);
    void memberFunction();
    void toEngine(const char* msg);
    int createChild(const char* szCommand);
    void quit();
    
private:
     pthread_t threads[1];

};
