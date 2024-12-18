//
//  globals.hpp
//  plants_watersystem
//
//  Created by Piotr Cieślik on 17/12/24.
//

#ifndef globals_h
#define globals_h

#include <concepts>
#include <ctime>
#include <map>
#include <stdio.h>
#include <string>
#include <vector>
#include <utility>

#define SENSOR_BUFFER 1024
#define TX_BUFFER 1024
#define RX_BUFFER 1024

#if __cplusplus > 201703L
#define CPP20
#elif __cplusplus > 201402L
#define CPP17
#elif _cplusplus > 199711L
#define CPP11
#else
#define CPPBASIC
#endif

typedef enum eState
{
    Idle = 0,
    Running,
    Stopped,
    Finished,
    Error
} State;

typedef enum eSensorType
{
    Temperature = 0,
    Humidity,
    Light
} SensorType;

typedef enum eCommunicatorType
{
    Receiver = 0,
    Transmitter
} CommunicatorType;

typedef enum eWorkerType
{
    Pump = 0,
    Dryier
} WorkerType;

#endif /* globals_h */
