//
//  Engine.hpp
//  Blackbird
//
//  Created by Mathias Dietrich on 6/14/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

#ifndef Engine_hpp
#define Engine_hpp

#include <stdio.h>
#include "Model.hpp"


class Engine{
    
public:
    Model *model =  new Model();
    
    void startPos(){
        model->startPos();
    }
    
};

#endif /* Engine_hpp */
