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
    template<typename U> inline U GetSingleData(int position = -1)
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
    
    template<typename U> size_t GetRawBuffer(U* retBuff, int dataSize = - 1)
    {
        size_t i = 0;

        if (std::is_integral_v<U> && std::is_unsigned_v<U> && dataSize > -1)
        {
            uint32_t* uData = (uint32_t*)(retBuff);

            for (; i < dataSize; i++)
                uData[i] = vBuffer[i];

            return i;
        }
        else if (std::is_same_v<U, char*> && dataSize > -1)
        {
            char** cData = (char**)(retBuff);

            for (; i < dataSize; i++)
                cData[i] = (char*)std::to_string(vBuffer[i]).c_str();

            return i;
        }
        else if (std::is_same_v<U, std::vector<uint32_t>>)
        {
            for (auto &elem : *retBuff)
            {
                elem = vBuffer[i];
                i++;
            }

            return i;
        }

        return dataSize;
    }
    
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
