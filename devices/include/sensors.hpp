//
//  sensors.hpp
//  plants_watersystem
//
//  Created by Piotr Cieślik on 17/12/24.
//

#ifndef sensors_hpp
#define sensors_hpp

#include "globals.hpp"
#include "device.hpp"

class Sensor : public Device<SensorType>
{
private:
    std::map<std::string, std::map<std::string, uint32_t>> historyData;
    std::map<std::string, std::map<std::string, uint32_t>>::iterator itHist;
    std::map<std::string, uint32_t>::iterator itTimed;

    size_t GetRawBuffer(uint32_t* buffer, int bufferSize);
    size_t GetRawBuffer(char* buffer[], int bufferSize);
    size_t GetRawBuffer(std::vector<uint32_t>* buffer);
public:
    Sensor(int sensorID, SensorType sensorType);
    virtual void Start() override;
    virtual uint32_t PollForConversion() = 0;
    virtual bool HalfCptCallback() = 0;
    virtual bool FullCptCallback() = 0;

    std::map<std::string, std::map<std::string, uint32_t>>* GetHistoryData();
    std::map<std::string, uint32_t>* GetTimedData(std::string date);
    uint32_t* GetSingleData(std::string date, std::string time);
    template<typename T> size_t GetRawBuffer(T* buffer, int bufferSize);

    ~Sensor();
};

class HumiditySensor : public Sensor
{
private:
    uint32_t buffer[SENSOR_BUFFER];
    size_t  bufferPosition;
public:
    HumiditySensor(int sensorID);

    virtual uint32_t PollForConversion() override;
    virtual bool HalfCptCallback() override;
    virtual bool FullCptCallback() override;

    ~HumiditySensor();
};

class TemperatureSensor : public Sensor
{
private:
    uint32_t buffer[SENSOR_BUFFER];
    size_t  bufferPosition;
public:
    TemperatureSensor(int sensorID);

    virtual uint32_t PollForConversion() override;
    virtual bool HalfCptCallback() override;
    virtual bool FullCptCallback() override;

    ~TemperatureSensor();
};

class LightSensor : public Sensor
{
private:
    uint32_t buffer[SENSOR_BUFFER];
    size_t  bufferPosition;
public:
    LightSensor(int sensorID);

    virtual uint32_t PollForConversion() override;
    virtual bool HalfCptCallback() override;
    virtual bool FullCptCallback() override;

    ~LightSensor();
};


#endif /* sensors_hpp */
