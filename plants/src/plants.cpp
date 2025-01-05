//
//  plants.cpp
//  plants_watersystem
//
//  Created by Piotr Cieślik on 18/12/24.
//

#include "plants.hpp"
#include <numeric>
#include <chrono>
#include <thread>

Plant::Plant(std::string name, int plantId) : sName(name), iPlantNum(plantId), iSensorsNum(0), iWorkersNum(0)
{
    printf("THIS IS PLANT ABSTRACT CONSTRUCTOR\n");
}

int Plant::AddSensor(SensorType sensorType, uint32_t lowValue, uint32_t highValue)
{
    Sensor* newSensor = nullptr;
    switch (sensorType)
    {
    case SensorType::Temperature:
        newSensor = new TemperatureSensor(iSensorsNum);
        break;
    case SensorType::Humidity:
        newSensor = new HumiditySensor(iSensorsNum);
        break;
    case SensorType::Light:
        newSensor = new LightSensor(iSensorsNum);
        break;
    default:
        break;
    }

    if (newSensor)
    {
        iSensorsNum++;
        mSensors.insert({newSensor, {lowValue, highValue}});
        mSensorMeanHourData.insert({newSensor, {{}}});
        return iSensorsNum;
    }

    return -1;
}

int Plant::AddWorker(WorkerType workerType)
{
    Worker* newWorker = nullptr;
    switch (workerType)
    {
    case WorkerType::Pump:
        newWorker = new PumpWorker(iWorkersNum);
        break;
    default:
        break;
    }

    if (newWorker)
    {
        iWorkersNum++;
        vWorkers.push_back(newWorker);
        return iWorkersNum;
    }

    return -1;
}

Sensor* Plant::RemoveSensor(int sensorId)
{
    Sensor* ret = nullptr;
    auto it = std::find_if(mSensors.begin(), mSensors.end(), [sensorId](const std::pair<Sensor*, std::pair<uint32_t, uint32_t>> & t) -> bool { return t.first->FindById(sensorId); });
    if (it != mSensors.end())
    {
        ret = it->first;
        mSensors.erase(it);

        auto itSensWorkMap = std::find_if(mSensorWorkerMap.begin(), mSensorWorkerMap.end(), [ret](const std::pair<Sensor*, Worker*> &t) -> bool { return t.first == ret; });
        if (itSensWorkMap != mSensorWorkerMap.end())
            mSensorWorkerMap.erase(itSensWorkMap);

        auto itSensMeanHourData = std::find_if(mSensorMeanHourData.begin(), mSensorMeanHourData.end(), [ret](const std::pair<Sensor*, std::map<std::string, std::map<std::string, uint32_t>>> &t) -> bool { return t.first == ret; });
        if (itSensMeanHourData != mSensorMeanHourData.end())
            mSensorMeanHourData.erase(itSensMeanHourData);
    }
        
    return ret;
}

Worker* Plant::RemoveWorker(int workerId)
{
    Worker* ret = nullptr;
    auto it = std::find_if(vWorkers.begin(), vWorkers.end(), [workerId](Worker* t) -> bool { return t->FindById(workerId); });
    if (it != vWorkers.end())
    {
        ret = *it;
        vWorkers.erase(it);
        
        auto itSensWorkMap = std::find_if(mSensorWorkerMap.begin(), mSensorWorkerMap.end(), [ret](const std::pair<Sensor*, Worker*> &t) -> bool { return t.second == ret; });
        if (itSensWorkMap != mSensorWorkerMap.end())
            mSensorWorkerMap.erase(itSensWorkMap);
    }
        
    return ret;
}

bool Plant::BindSensorWorker(int sensorId, int workerId)
{
    auto itSens = std::find_if(mSensors.begin(), mSensors.end(), [sensorId](const std::pair<Sensor*, std::pair<uint32_t, uint32_t>> &t) -> bool { return t.first->FindById(sensorId); });
    auto itWorker = std::find_if(vWorkers.begin(), vWorkers.end(), [workerId](Worker* t) -> bool { return t->FindById(workerId); });
    if (itSens != mSensors.end() && itWorker != vWorkers.end())
    {
        mSensorWorkerMap.insert_or_assign(itSens->first, *itWorker);
        return true;
    }

    return false;
}

void Plant::Run()
{
    while (true)
    {

        for (auto &[keySens, timedSens] : mSensorMeanHourData)
        {
            std::string sTime;
            GetTime<std::string>(&sTime);
            std::string sDay;
            GetDate<std::string>(&sDay);
            
            std::map<std::string, std::map<std::string, uint32_t>>::iterator date = timedSens.find(sDay);
            auto time = std::prev(date->second.end());

            if (date == timedSens.end())
            {
                auto [date, time] = timedSens.insert({sDay, {{sTime, 0}}});
            }

            if (std::stoi(sTime) - std::stoi(time->first) > 5)
            {
                std::vector<uint32_t> sensData;
                keySens->GetRawBuffer<std::vector<uint32_t>>(&sensData);

                uint32_t meanValue = std::accumulate(sensData.begin(), sensData.end(), 0) / sensData.size();
                date->second.insert_or_assign(sTime, meanValue);
            }

            auto worker = mSensorWorkerMap.find(keySens);
            if (worker->second->GetState() != State::Running && time->second < mSensors.find(keySens)->second.first)
            {
                mSensorWorkerMap.find(keySens)->second->DoWork();
                std::this_thread::sleep_for(std::chrono::seconds(30));
                mSensorWorkerMap.find(keySens)->second->Stop();
            }
        }
        std::this_thread::sleep_for(std::chrono::minutes(10));
    }

    
}

int Plant::CheckState()
{
    int retVal = -1; // meaning no sensors found
    std::string sTime;
    GetTime<std::string>(&sTime);
    std::string sDate;
    GetDate<std::string>(&sDate);

    for (auto &[keySensor, value] : mSensors)
    {
        auto sensorIt = mSensorMeanHourData.find(keySensor);
        if (sensorIt != mSensorMeanHourData.end())
        {
            auto dateIt = sensorIt->second.find(sDate);
            if (dateIt != sensorIt->second.end())
            {
                auto timeIt = dateIt->second.find(sTime);
                if (timeIt != dateIt->second.end() && (timeIt->second < value.first || timeIt->second > value.second))
                    retVal = keySensor->GetID();
            }
        }
    }
    
    return retVal;
}

void Plant::DoWork(int workerId)
{

}

template<typename T> size_t Plant::GetHourData(int sensorId, std::string date, std::string hour, T* retBuff, int bufferSize /*= -1*/)
{

}

template<typename T> T Plant::GetMeanDailyValue(int sensorId, std::string date)
{

}

Plant::~Plant()
{

}
