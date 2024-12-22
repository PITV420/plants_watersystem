//
//  workers.hpp
//  plants_watersystem
//
//  Created by Piotr Cieślik on 17/12/24.
//

#ifndef workers_hpp
#define workers_hpp

#include "device.hpp"
#include "globals.hpp"

class Worker : public Device<WorkerType>
{
public:
    Worker(int workerID, WorkerType workerType);
    virtual void Start() override;
    virtual void DoWork() = 0;
    ~Worker();
};

class PumpWorker : public Worker
{
public:
    PumpWorker(int workerID);
    virtual void DoWork() override;
    ~PumpWorker();
};

#endif /* workers_hpp */
