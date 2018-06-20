//
//  Observer.hpp
//  Blackbird
//
//  Created by Mathias Dietrich on 6/17/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <vector>
#include "Ply.hpp"

using namespace std;

class  Observer
{
    
public:
    virtual void makeMoveWhite(Ply ply) = 0;
    virtual void makeMoveBlack(Ply ply) = 0;
    virtual void logEngine(string msg) = 0;
};




