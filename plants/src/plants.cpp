//
//  plants.cpp
//  plants_watersystem
//
//  Created by Piotr Cieślik on 18/12/24.
//

#include "plants.hpp"

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
    }
        
    return ret;
}

bool Plant::BindSensorWorker(int sensorId, int workerId)
{
    auto itSensor = std::find_if(mSensors.begin(), mSensors.end(), [sensorId](const std::pair<Sensor*, std::pair<uint32_t, uint32_t>> & t) -> bool { return t.first->FindById(sensorId); });
    auto itWork = std::find_if(vWorkers.begin(), vWorkers.end(), [workerId](Worker* t) -> bool { return t->FindById(workerId); });

    if (itSensor != mSensors.end() && itWork != vWorkers.end())
    {
        mSensorWorkerMap.insert_or_assign(itSensor->first->GetID(), (*itWork)->GetID());
        return true;
    }
    
    return false;
}

void Plant::Run()
{

}

int Plant::CheckState()
{
    return -1;
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
