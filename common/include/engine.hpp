//
//  engine.hpp
//  plants_watersystem
//
//  Created by Piotr Cieślik on 18/12/24.
//

#ifndef engine_hpp
#define engine_hpp

#include "globals.hpp"

class Engine
{
private:
    static Engine* instance;
    Engine();
#ifdef CPPBASIC
    Engine(Engine &const);
    void operator=(Engine &const);
#endif
public:
    Engine* GetInstance();
#ifndef CPPBASIC
    Engine(Engine &other) = delete;
    void operator=(const Engine &) = delete;
#endif
    ~Engine();
};

#endif /* engine_hpp */
