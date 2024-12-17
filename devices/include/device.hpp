//
//  device.hpp
//  plants_watersystem
//
//  Created by Piotr Cieślik on 17/12/24.
//

#ifndef device_hpp
#define device_hpp

#include <stdio.h>
#include <ctime>
#include "globals.hpp"

template<typename T> class Device
{
private:
    const int deviceID;
    volatile State runState;
    const T deviceType;
protected:
    time_t now;
    tm *ltm;
public:
    Device(int deviceID, T deviceType);
    
    virtual void Start() = 0;
    virtual void Stop();

    const int GetID();
    State GetState();
    T GetType();

    ~Device();
};

#endif /* device_hpp */
