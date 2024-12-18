//
//  sensors.cpp
//  plants_watersystem
//
//  Created by Piotr Cieślik on 17/12/24.
//

#include <concepts>
#include "sensors.hpp"

Sensor::Sensor(int sensorID, SensorType sensorType) : Device<SensorType>(sensorID, sensorType)
{
    printf("THIS IS SENSOR ABSTRACTION CONSTRUCTOR\n");
}

size_t Sensor::GetRawBuffer(uint32_t* buffer, int bufferSize)
{
    if (itHist == historyData.end())
    {
        itHist = historyData.begin();
        itTimed = itHist->second.begin();
    }

    int i = 0;
    while (itHist != historyData.end())
    {
        for (; itTimed != itHist->second.end() && i < bufferSize; itTimed++, i++)
            buffer[i] = itTimed->second;

        itHist++;
        itTimed = itHist->second.begin();
    }

    return i;
}

size_t Sensor::GetRawBuffer(char* buffer[], int bufferSize)
{
    if (itHist == historyData.end())
    {
        itHist = historyData.begin();
        itTimed = itHist->second.begin();
    }

    int i = 0;
    while (itHist != historyData.end())
    {
        for (; itTimed != itHist->second.end() && i < bufferSize; itTimed++, i++)
            buffer[i] = (char*)(std::to_string(itTimed->second).c_str());

        itHist++;
        itTimed = itHist->second.begin();
    }

    return i;
}

size_t Sensor::GetRawBuffer(std::vector<uint32_t>* buffer)
{
    buffer->clear();

    if (itHist == historyData.end())
    {
        itHist = historyData.begin();
        itTimed = itHist->second.begin();
    }

    while (itHist != historyData.end())
    {
        for (; itTimed != itHist->second.end(); itTimed++)
            buffer->push_back(itTimed->second);

        itHist++;
        itTimed = itHist->second.begin();
    }

    return buffer->size();
}

void Sensor::Start()
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

        std::map<std::string, std::map<std::string, uint32_t>>::iterator it = historyData.find(day + month + year);
        if (it != historyData.end())
            it->second.insert_or_assign(day + month + year, PollForConversion());
        else
        {
            std::string insertDate = day + month + year;
            std::map<std::string, uint32_t> newData = {{hour + minute, PollForConversion()}};
            historyData.insert({insertDate, newData});
        }
    }
}

std::map<std::string, std::map<std::string, uint32_t>>* Sensor::GetHistoryData()
{
    return &historyData;
}

std::map<std::string, uint32_t>* Sensor::GetTimedData(std::string date)
{
    auto it = historyData.find(date);
    if (it != historyData.end())
        return &it->second;

    return nullptr;
}

uint32_t* Sensor::GetSingleData(std::string date, std::string time)
{
    auto it = GetTimedData(date);
    if (it)
    {
        auto it2 = it->find(time);
        if (it2 != it->end())
            return &it2->second;
    }

    return nullptr;
}

template<typename U> size_t Sensor::GetRawBuffer(U* buffer, int bufferSize)
{
    if (std::is_same_v<U, uint32_t*>)
    {
        return GetRawBuffer((uint32_t*)buffer, bufferSize);
    }
    else if (std::is_same_v<U, char**>)
    {
        return GetRawBuffer((char**)buffer, bufferSize);
    }
    else if (std::is_same_v<U, std::vector<uint32_t>>)
        return GetRawBuffer(static_cast<std::vector<uint32_t>*>(buffer));

    return 0;
}

Sensor::~Sensor()
{
    printf("THIS IS SENSOR ABSTRACTION DESTRUCTOR\n");
}

HumiditySensor::HumiditySensor(int sensorID) : Sensor(sensorID, SensorType::Humidity)
{
    memset(buffer, 0, SENSOR_BUFFER);
    printf("THIS IS HUMIDITY CONSTRUCTOR\n");
}

uint32_t HumiditySensor::PollForConversion()
{
    // TODO
    bufferPosition++;
    if (bufferPosition >= SENSOR_BUFFER)
        bufferPosition = 0;
    
    return 0;
}

bool HumiditySensor::HalfCptCallback()
{
    if (bufferPosition >= SENSOR_BUFFER / 2)
        return true;
    
    return false;
}

bool HumiditySensor::FullCptCallback()
{
    if (bufferPosition >= SENSOR_BUFFER)
        return true;
    
    return false;
}

HumiditySensor::~HumiditySensor()
{
    printf("THIS IS HUMIDITY DESTRUCTOR\n");
}

TemperatureSensor::TemperatureSensor(int sensorID) : Sensor(sensorID, SensorType::Temperature)
{
    memset(buffer, 0, SENSOR_BUFFER);
    printf("THIS IS TEMPERATURE CONSTRUCTOR\n");
}

uint32_t TemperatureSensor::PollForConversion()
{
    // TODO
    bufferPosition++;
    if (bufferPosition >= SENSOR_BUFFER)
        bufferPosition = 0;
    
    return 0;
}

bool TemperatureSensor::HalfCptCallback()
{
    if (bufferPosition >= SENSOR_BUFFER / 2)
        return true;
    
    return false;
}

bool TemperatureSensor::FullCptCallback()
{
    if (bufferPosition >= SENSOR_BUFFER)
        return true;
    
    return false;
}

TemperatureSensor::~TemperatureSensor()
{
    printf("THIS IS TEMPERATURE DESTRUCTOR\n");
}

LightSensor::LightSensor(int sensorID) : Sensor(sensorID, SensorType::Light)
{
    memset(buffer, 0, SENSOR_BUFFER);
    printf("THIS IS HUMIDITY CONSTRUCTOR\n");
}

uint32_t LightSensor::PollForConversion()
{
    // TODO
    bufferPosition++;
    if (bufferPosition >= SENSOR_BUFFER)
        bufferPosition = 0;
    
    return 0;
}

bool LightSensor::HalfCptCallback()
{
    if (bufferPosition >= SENSOR_BUFFER / 2)
        return true;
    
    return false;
}

bool LightSensor::FullCptCallback()
{
    if (bufferPosition >= SENSOR_BUFFER)
        return true;
    
    return false;
}

LightSensor::~LightSensor()
{
    printf("THIS IS HUMIDITY DESTRUCTOR\n");
}