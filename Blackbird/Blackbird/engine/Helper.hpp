//
//  Helper.h
//  Blackbird
//
//  Created by Mathias Dietrich on 6/15/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <string>
#include <iostream>

#include "Const.hpp"

using namespace std;

class Helper{
public:
    void printBitboard(uint64_t board){
        
        cout << "  A B C D E F G H" << endl;
        const uint64_t s = 1;
        
        for(int r=0;r<8;r++){
            cout << 8-r << " ";
            for(int c=0;c<8;c++){
                uint64_t pos = c + (7-r) * 8;
                
                uint64_t comp =  s << pos;
                if(comp & board){
                    cout << "1" << " ";
                }else{
                    cout << "0" << " ";
                }
            }
            cout << 8-r << endl;
        }
        cout << "  A B C D E F G H" << endl;
    }
};


