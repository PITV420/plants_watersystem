//
//  engine.cpp
//  plants_watersystem
//
//  Created by Piotr Cieślik on 18/12/24.
//

#include "engine.hpp"
#include <stdio.h>

Engine* Engine::eInstance = nullptr;

Engine::Engine()
{
    printf("THIS IS ENGINE SINGLETON CONSTRUCTOR. YOU CAN SEE THIS ONLY ONCE!\n");
}

Engine* Engine::GetInstance()
{
    if (!eInstance)
        eInstance = new Engine();
    
    return eInstance;
}
