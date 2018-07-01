//
//  main.cpp
//  BlackirdEngine
//
//  Created by Mathias Dietrich on 6/29/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

#include <iostream>
#include "../Blackbird/engine/Analyzer.hpp"
#include "../Blackbird/engine/Observer.hpp"
#include "../Blackbird/engine/Global.hpp"

#include "Uci.hpp"

using namespace std;

int main(int argc, const char * argv[]) {

    Uci *uci = new Uci();
    uci->isEmbedded = false;
    
    uci->listen("uci");
    
    string fen = "position fen rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    uci->listen(fen);
    
    string go = "go movetime 5000";
    uci->listen(go);
    
    bool isRunning = true;
    while(isRunning){
        std::string cmd;
        std::getline (std::cin, cmd);
        isRunning = uci->listen(cmd);
    }

    return 0;
}
