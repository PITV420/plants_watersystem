//
//  sensors.cpp
//  plants_watersystem
//
//  Created by Piotr Cieślik on 17/12/24.
//

#include "sensors.hpp"

Sensor::Sensor(int sensorID, SensorType sensorType) : Device<SensorType>(sensorID, sensorType)
{
    vIt = vBuffer.begin();
    printf("THIS IS SENSOR ABSTRACTION CONSTRUCTOR\n");
}

void Sensor::Start()
{
    sRunState = State::Running;

    while (sRunState == State::Running)
    {
        *vIt = PollForConversion();
        vIt++;

        if (vIt == vBuffer.end())
            vIt = vBuffer.begin();
    }
}

Sensor::~Sensor()
{
    printf("THIS IS SENSOR ABSTRACTION DESTRUCTOR\n");
}

HumiditySensor::HumiditySensor(int sensorID) : Sensor(sensorID, SensorType::Humidity)
{
    memset(uBuffer, 0, SENSOR_BUFFER);
    uBufferPosition = 0;
    printf("THIS IS HUMIDITY CONSTRUCTOR\n");
}

uint32_t HumiditySensor::PollForConversion()
{
    // TODO
    uBufferPosition++;
    if (uBufferPosition >= SENSOR_BUFFER)
        uBufferPosition = 0;
    
    return 0;
}

bool HumiditySensor::HalfCptCallback()
{
    if (uBufferPosition >= SENSOR_BUFFER / 2)
        return true;
    
    return false;
}

bool HumiditySensor::FullCptCallback()
{
    if (uBufferPosition >= SENSOR_BUFFER)
        return true;
    
    return false;
}

HumiditySensor::~HumiditySensor()
{
    printf("THIS IS HUMIDITY DESTRUCTOR\n");
}

TemperatureSensor::TemperatureSensor(int sensorID) : Sensor(sensorID, SensorType::Temperature)
{
    memset(uBuffer, 0, SENSOR_BUFFER);
    uBufferPosition = 0;
    printf("THIS IS TEMPERATURE CONSTRUCTOR\n");
}

uint32_t TemperatureSensor::PollForConversion()
{
    // TODO
    uBufferPosition++;
    if (uBufferPosition >= SENSOR_BUFFER)
        uBufferPosition = 0;
    
    return 0;
}

bool TemperatureSensor::HalfCptCallback()
{
    if (uBufferPosition >= SENSOR_BUFFER / 2)
        return true;
    
    return false;
}

bool TemperatureSensor::FullCptCallback()
{
    if (uBufferPosition >= SENSOR_BUFFER)
        return true;
    
    return false;
}

TemperatureSensor::~TemperatureSensor()
{
    printf("THIS IS TEMPERATURE DESTRUCTOR\n");
}

LightSensor::LightSensor(int sensorID) : Sensor(sensorID, SensorType::Light)
{
    memset(uBuffer, 0, SENSOR_BUFFER);
    uBufferPosition = 0;
    printf("THIS IS HUMIDITY CONSTRUCTOR\n");
}

uint32_t LightSensor::PollForConversion()
{
    // TODO
    uBufferPosition++;
    if (uBufferPosition >= SENSOR_BUFFER)
        uBufferPosition = 0;
    
    return 0;
}

bool LightSensor::HalfCptCallback()
{
    if (uBufferPosition >= SENSOR_BUFFER / 2)
        return true;
    
    return false;
}

bool LightSensor::FullCptCallback()
{
    if (uBufferPosition >= SENSOR_BUFFER)
        return true;
    
    return false;
}

LightSensor::~LightSensor()
{
    printf("THIS IS HUMIDITY DESTRUCTOR\n");
}
