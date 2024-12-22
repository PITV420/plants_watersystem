//
//  workers.cpp
//  plants_watersystem
//
//  Created by Piotr Cieślik on 17/12/24.
//

#include "workers.hpp"

Worker::Worker(int workerID, WorkerType workerType) : Device<WorkerType>(workerID, workerType)
{
    printf("THIS IS WORKER ABSTRACTION CONSTRUCTOR\n");
}

void Worker::Start()
{
    sRunState = State::Running;
    while (sRunState == State::Running)
    {
        DoWork();
    }
}

Worker::~Worker()
{
    printf("THIS IS WORKER ABSTRACTION DESTRUCTOR\n");
}

PumpWorker::PumpWorker(int workerID) : Worker(workerID, WorkerType::Pump)
{
    printf("THIS IS PUMP CONSTRUCTOR\n");
}

void PumpWorker::DoWork()
{
    // TODO
}

PumpWorker::~PumpWorker()
{
    printf("THIS IS PUMP DESTRUCTOR\n");
}