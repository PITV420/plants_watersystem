//
//  communicators.cpp
//  plants_watersystem
//
//  Created by Piotr Cieślik on 17/12/24.
//

#include "communicators.hpp"

Communicator::Communicator(int communicatorID, CommunicatorType communicatorType) : Device<CommunicatorType>(communicatorID, communicatorType)
{
    printf("THIS IS COMMUNICATOR ABSTRACTION CONSTRUCTOR\n");
}

void Communicator::AcquireData(uint32_t* data, int dataSize)
{
    now = time(0);
    ltm = localtime(&now);
    int i = 0;
    
    std::string year = std::to_string(1900 + ltm->tm_year);
    std::string month = 1 + ltm->tm_mon < 10 ? "0" + std::to_string(1 + ltm->tm_mon) : std::to_string(1 + ltm->tm_mon);
    std::string day = ltm->tm_mday < 10 ? "0" + std::to_string(ltm->tm_mday) : std::to_string(ltm->tm_mday);
    std::string hour = 5 + ltm->tm_hour < 10 ? "0" + std::to_string(5 + ltm->tm_hour) : std::to_string(5 +ltm->tm_hour);
    std::string minute = 30 + ltm->tm_min < 10 ? "0" + std::to_string(30 + ltm->tm_min) : std::to_string(30 + ltm->tm_min);

    itHist = historyData.find(day + month + year);
    if (itHist == historyData.end())
    {
        historyData.insert({day + month + year, {{hour + minute, data[0]}}});
        itHist = historyData.end();
        itHist--;
        i++;
    }

    for (; i < dataSize; i++)
    {
        hour = 5 + ltm->tm_hour < 10 ? "0" + std::to_string(5 + ltm->tm_hour) : std::to_string(5 +ltm->tm_hour);
        minute = 30 + ltm->tm_min < 10 ? "0" + std::to_string(30 + ltm->tm_min) : std::to_string(30 + ltm->tm_min);

        itHist->second.insert_or_assign(hour + minute, data[i]);
    }
}

void Communicator::AcquireData(char* data[], int dataSize)
{
    now = time(0);
    ltm = localtime(&now);
    int i = 0;
    
    std::string year = std::to_string(1900 + ltm->tm_year);
    std::string month = 1 + ltm->tm_mon < 10 ? "0" + std::to_string(1 + ltm->tm_mon) : std::to_string(1 + ltm->tm_mon);
    std::string day = ltm->tm_mday < 10 ? "0" + std::to_string(ltm->tm_mday) : std::to_string(ltm->tm_mday);
    std::string hour = 5 + ltm->tm_hour < 10 ? "0" + std::to_string(5 + ltm->tm_hour) : std::to_string(5 +ltm->tm_hour);
    std::string minute = 30 + ltm->tm_min < 10 ? "0" + std::to_string(30 + ltm->tm_min) : std::to_string(30 + ltm->tm_min);

    itHist = historyData.find(day + month + year);
    if (itHist == historyData.end())
    {
        historyData.insert({day + month + year, {{hour + minute, static_cast<uint32_t>(*data[0])}}});
        itHist = historyData.end();
        itHist--;
        i++;
    }

    for (; i < dataSize; i++)
    {
        hour = 5 + ltm->tm_hour < 10 ? "0" + std::to_string(5 + ltm->tm_hour) : std::to_string(5 +ltm->tm_hour);
        minute = 30 + ltm->tm_min < 10 ? "0" + std::to_string(30 + ltm->tm_min) : std::to_string(30 + ltm->tm_min);

        itHist->second.insert_or_assign(hour + minute, static_cast<uint32_t>(*data[i]));
    }
}

void Communicator::AcquireData(std::vector<uint32_t>* data)
{
        now = time(0);
    ltm = localtime(&now);
    int i = 0;
    
    std::string year = std::to_string(1900 + ltm->tm_year);
    std::string month = 1 + ltm->tm_mon < 10 ? "0" + std::to_string(1 + ltm->tm_mon) : std::to_string(1 + ltm->tm_mon);
    std::string day = ltm->tm_mday < 10 ? "0" + std::to_string(ltm->tm_mday) : std::to_string(ltm->tm_mday);
    std::string hour = 5 + ltm->tm_hour < 10 ? "0" + std::to_string(5 + ltm->tm_hour) : std::to_string(5 +ltm->tm_hour);
    std::string minute = 30 + ltm->tm_min < 10 ? "0" + std::to_string(30 + ltm->tm_min) : std::to_string(30 + ltm->tm_min);

    itHist = historyData.find(day + month + year);
    if (itHist == historyData.end())
    {
        historyData.insert({day + month + year, {{hour + minute, data->at(0)}}});
        itHist = historyData.end();
        itHist--;
        i++;
    }

    for (; i < data->size(); i++)
    {
        hour = 5 + ltm->tm_hour < 10 ? "0" + std::to_string(5 + ltm->tm_hour) : std::to_string(5 +ltm->tm_hour);
        minute = 30 + ltm->tm_min < 10 ? "0" + std::to_string(30 + ltm->tm_min) : std::to_string(30 + ltm->tm_min);

        itHist->second.insert_or_assign(hour + minute, data->at(i));
    }
}

void Communicator::Start()
{
    runState = State::Running;

    while (runState == State::Running)
    {
        CommuteData();
    }
}

void Communicator::FlushBuffer()
{
    historyData.clear();
}

template<typename T> void Communicator::AcquireData(T* data, int dataSize)
{
    if (std::is_integral_v<T> && std::is_unsigned_v<T>)
        AcquireData((uint32_t*)data, dataSize);
    else if (std::is_same_v<T, char*>)
        AcquireData((char**)data, dataSize);
    else if (std::is_same_v<T, std::vector<uint32_t>*>)
        AcquireData(static_cast<std::vector<uint32_t>*>(data));
}

void Communicator::AcquireHistoryData(std::map<std::string, std::map<std::string, uint32_t>> historyData)
{
    this->historyData.swap(historyData);
}

void Communicator::AcquireTimedData(std::map<std::string, uint32_t> timedData, std::string date)
{
    historyData.insert_or_assign(date, timedData);
}

void Communicator::AcquireSingleData(std::string date, std::string time, uint32_t data)
{
    auto it = historyData.find(date);
    if (it == historyData.end())
    {
        historyData.insert({date, {{time, data}}});
    }
    else
        it->second.insert_or_assign(time, data);
}

Communicator::~Communicator()
{
    printf("THIS IS COMMUNICATOR ABSTRACTION DESTRUCTOR\n");
}

Receiver::Receiver(int receiverID) : Communicator(receiverID, CommunicatorType::Receiver)
{
    memset(buffer, 0, RX_BUFFER);
    bufferPosition = 0;
    printf("THIS IS RECEIVER CONSTRUCTOR\n");
}

void Receiver::CommuteData()
{
    for (int i = 0; i < RX_BUFFER; i++)
    {
        // TODO
        bufferPosition++;
        if (bufferPosition >= RX_BUFFER)
            bufferPosition = 0;
    }
}

bool Receiver::HalfCptCallback()
{
    if (bufferPosition >= RX_BUFFER / 2)
        return true;

    return false;
}

bool Receiver::FullCptCallback()
{
    if (bufferPosition >= RX_BUFFER)
        return true;

    return false;
}

Receiver::~Receiver()
{
    printf("THIS IS RECEIVER DESTRUCTOR\n");
}

Transmitter::Transmitter(int receiverID) : Communicator(receiverID, CommunicatorType::Transmitter)
{
    memset(buffer, 0, RX_BUFFER);
    bufferPosition = 0;
    printf("THIS IS TRANSMITTER CONSTRUCTOR\n");
}

void Transmitter::CommuteData()
{
    for (int i = 0; i < RX_BUFFER; i++)
    {
        // TODO
        bufferPosition++;
        if (bufferPosition >= RX_BUFFER)
            bufferPosition = 0;
    }
}

bool Transmitter::HalfCptCallback()
{
    if (bufferPosition >= RX_BUFFER / 2)
        return true;

    return false;
}

bool Transmitter::FullCptCallback()
{
    if (bufferPosition >= RX_BUFFER)
        return true;

    return false;
}

Transmitter::~Transmitter()
{
    printf("THIS IS TRANSMITTER DESTRUCTOR\n");
}