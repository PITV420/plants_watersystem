//
//  device.cpp
//  plants_watersystem
//
//  Created by Piotr Cieślik on 17/12/24.
//

#include "device.hpp"

template<typename T> Device<T>::Device(int deviceID, T deviceType) : deviceID(deviceID), deviceType(deviceType)
{
    runState = State::Idle;
    printf("THIS IS DEVICE ABSTRACTION CONSTRUCTOR\n");
}

template<typename T> void Device<T>::Stop()
{
    runState = State::Stopped;
}

template<typename T> const int Device<T>::GetID()
{
    return deviceID;
}

template<typename T> State Device<T>::GetState()
{
    return runState;
}

template<typename T> T Device<T>::GetType()
{
    return deviceType;
}

template<typename T> Device<T>::~Device()
{
    printf("THIS IS DEVICE ABSTRACTION DESTRUCTOR\n");
}

template class Device<SensorType>;
template class Device<CommunicatorType>;
template class Device<WorkerType>;
