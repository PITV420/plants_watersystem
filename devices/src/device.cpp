//
//  device.cpp
//  plants_watersystem
//
//  Created by Piotr Cieślik on 17/12/24.
//

#include "device.hpp"

template<typename T> Device<T>::Device(int deviceID, T deviceType) : ciDeviceID(deviceID), tDeviceType(deviceType)
{
    sRunState = State::Idle;
    printf("THIS IS DEVICE ABSTRACTION CONSTRUCTOR\n");
}

template<typename T> void Device<T>::Stop()
{
    sRunState = State::Stopped;
}

template<typename T> const int Device<T>::GetID()
{
    return ciDeviceID;
}

template<typename T> State Device<T>::GetState()
{
    return sRunState;
}

template<typename T> T Device<T>::GetType()
{
    return tDeviceType;
}

template<typename T> Device<T>* Device<T>::FindById(int deviceID)
{
    if (ciDeviceID == deviceID)
        return this;
    
    return nullptr;
}

template<typename T> Device<T>::~Device()
{
    printf("THIS IS DEVICE ABSTRACTION DESTRUCTOR\n");
}

template class Device<SensorType>;
template class Device<CommunicatorType>;
template class Device<WorkerType>;
