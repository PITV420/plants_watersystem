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
private:
    std::string scheduleDate;
    std::string startTime;
    std::string endTime;
public:
    Worker(int workerID, WorkerType workerType);

    virtual void Start() override;
    virtual void DoWork() = 0;
    void ScheduleWork(std::string date, std::string time, std::string end);

    ~Worker();
};

class Pump : public Worker
{
public:
    Pump(int workerID);
    virtual void DoWork() override;
    ~Pump();
};

#endif /* workers_hpp */
