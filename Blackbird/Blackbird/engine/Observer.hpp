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

using namespace std;

class  Observer
{
    
public:
    virtual void makeMove(int from, int to) = 0;
};




