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

template<typename U> U Sensor::GetSingleData(int position /*= -1*/)
{
    uint32_t value = position < 0 ? *vIt : vBuffer[position];
    if (std::is_integral_v<U> && std::is_unsigned_v<U>)
        return (U)(value);
    else if (std::is_same_v<U, char>)
    {
        return (U)(*std::to_string(value).c_str());
    }
    return -1;
}

template<typename U> size_t Sensor::GetRawBuffer(U* retBuff, int dataSize /*= -1*/)
{
    size_t i = 0;

    if (std::is_integral_v<U> && std::is_unsigned_v<U> && dataSize > -1)
    {
        uint32_t* uData = static_cast<uint32_t*>(retBuff);

        for (; i < dataSize; i++)
            uData[i] = vBuffer[i];

        return i;
    }
    else if (std::is_same_v<U, char*> && dataSize > -1)
    {
        char** cData = static_cast<char**>(retBuff);

        for (; i < dataSize; i++)
            cData[i] = (char*)std::to_string(vBuffer[i]).c_str();

        return i;
    }
    else if (std::is_array_v<U>)
    {
        for (auto &elem : static_cast<std::vector<uint32_t>>(*retBuff))
        {
            elem = vBuffer[i];
            i++;
        }

        return i;
    }

    return dataSize;
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