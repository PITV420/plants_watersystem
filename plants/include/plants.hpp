//
//  plants.hpp
//  plants_watersystem
//
//  Created by Piotr Cieślik on 18/12/24.
//

#ifndef plants_hpp
#define plants_hpp

#include "globals.hpp"
#include "sensors.hpp"
#include "workers.hpp"

class Plant
{
private:
    const std::string sName;
    const int iPlantNum;

    std::map<Sensor*, std::pair<uint32_t, uint32_t>> mSensors;
    int iSensorsNum;

    std::vector<Worker*> vWorkers;
    int iWorkersNum;

    std::map<int, int> mSensorWorkerMap;

    time_t tNow;
    tm* tLtm;

    std::map<std::map<int, std::string>, std::map<std::string, uint32_t>> mSensorMeanHourData;
public:
    Plant(std::string name, int plantId);
    int AddSensor(SensorType sensorType, uint32_t lowValue, uint32_t highValue);
    int AddWorker(WorkerType workerType);
    Sensor* RemoveSensor(int sensorId);
    Worker* RemoveWorker(int workerId);
    bool BindSensorWorker(int sensorId, int workerId);

    virtual void Run();
    virtual int CheckState();
    virtual void DoWork(int workerId);

    template<typename T> size_t GetHourData(int sensorId, std::string date, std::string hour, T* retBuff, int bufferSize = -1);
    template<typename T> T GetMeanDailyValue(int sensorId, std::string date);
    ~Plant();
};

#endif /* plants_hpp */
