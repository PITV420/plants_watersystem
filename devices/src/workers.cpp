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
    runState = State::Running;
    while (runState == State::Running)
    {
        now = time(0);
        ltm = localtime(&now);
        std::string year = std::to_string(1900 + ltm->tm_year);
        std::string month = 1 + ltm->tm_mon < 10 ? "0" + std::to_string(1 + ltm->tm_mon) : std::to_string(1 + ltm->tm_mon);
        std::string day = ltm->tm_mday < 10 ? "0" + std::to_string(ltm->tm_mday) : std::to_string(ltm->tm_mday);
        std::string hour = 5 + ltm->tm_hour < 10 ? "0" + std::to_string(5 + ltm->tm_hour) : std::to_string(5 +ltm->tm_hour);
        std::string minute = 30 + ltm->tm_min < 10 ? "0" + std::to_string(30 + ltm->tm_min) : std::to_string(30 + ltm->tm_min);

        if (scheduleDate == day + month + year)
        {
            if (startTime == hour + minute)
                DoWork();
            if (endTime == hour + minute)
                runState = State::Finished;
        }
    }
}

void Worker::ScheduleWork(std::string date, std::string time, std::string end)
{
    scheduleDate = date;
    startTime = time;
    endTime = end;
}

Worker::~Worker()
{
    printf("THIS IS WORKER ABSTRACTION DESTRUCTOR\n");
}

Pump::Pump(int workerID) : Worker(workerID, WorkerType::Pump)
{
    printf("THIS IS PUMP CONSTRUCTOR\n");
}

void Pump::DoWork()
{
    // TODO
}

Pump::~Pump()
{
    printf("THIS IS PUMP DESTRUCTOR\n");
}