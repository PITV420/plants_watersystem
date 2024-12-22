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
    std::vector<uint32_t> vBuffer;
    std::vector<uint32_t>::iterator vIt;
public:
    Sensor(int sensorID, SensorType sensorType);
    virtual void Start() override;
    virtual uint32_t PollForConversion() = 0;
    virtual bool HalfCptCallback() = 0;
    virtual bool FullCptCallback() = 0;
    template<typename U> U GetSingleData(int position = -1);
    template<typename U> size_t GetRawBuffer(U* retBuff, int dataSize = - 1);
    ~Sensor();
};

class HumiditySensor : public Sensor
{
private:
    uint32_t uBuffer[SENSOR_BUFFER];
    size_t  uBufferPosition;
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
    uint32_t uBuffer[SENSOR_BUFFER];
    size_t  uBufferPosition;
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
    uint32_t uBuffer[SENSOR_BUFFER];
    size_t  uBufferPosition;
public:
    LightSensor(int sensorID);
    virtual uint32_t PollForConversion() override;
    virtual bool HalfCptCallback() override;
    virtual bool FullCptCallback() override;
    ~LightSensor();
};


#endif /* sensors_hpp */
