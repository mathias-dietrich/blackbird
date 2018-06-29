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

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    Analyzer *analyzer = new Analyzer();
    analyzer->analyze(0,0,"");
    return 0;
}
