//
//  Engine.hpp
//  Blackbird
//
//  Created by Mathias Dietrich on 6/14/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

#pragma once

#include <stdio.h>
#include "Model.hpp"
#include "MoveGen.hpp"'

class Engine{
 
private:
    Engine(){
        model =  new Model();
    }
    
    static  Engine * m_pInstance;
    
public:

    
    MoveGen *gen = new MoveGen();
    
    static Engine * Instance()
    {
        if (NULL == m_pInstance){  
            m_pInstance = new Engine;
        }
        return m_pInstance;
    }
    
    Model *model;
    
    void startPos(){
        model->startPos();
    }
    
    void newWhite(){
         model->isFlipped = false;
         model->startPos();
        model->whiteToMove = true;
    }
    
    void newBlack(){
         model->startPos();
        model->isFlipped = true;
        model->whiteToMove = false;
    }
    
    void flip(){
        model->isFlipped =  !model->isFlipped ;
    }
};

Engine * Engine::m_pInstance = NULL;

