//
//  Move.hpp
//  Blackbird
//
//  Created by Mathias Dietrich on 6/16/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <string>
#include <iostream>

#include "Const.h"

using namespace std;

class Move{
    
public:
    int id;
    int w_from;
    int w_to;
    int w_figure;
    int b_from;
    int b_to;
    int b_figure;
    string w_move;
    string b_move;
    string comment;
    
};

