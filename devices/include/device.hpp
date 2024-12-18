//
//  device.hpp
//  plants_watersystem
//
//  Created by Piotr Cieślik on 17/12/24.
//

#ifndef device_hpp
#define device_hpp

#include "globals.hpp"

template<typename T> class Device
{
private:
    const int deviceID;
    const T deviceType;
protected:
    volatile State runState;
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
