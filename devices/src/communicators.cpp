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
    vIt = vBuffer.begin();
}

#if 0
template<isUint U> void Communicator::AcquireData(U* data, int dataSize)
{
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
    }

    for (std::array dataArr = std::to_array<uint32_t>(data); auto &e : dataArr)
    {
        hour = 5 + ltm->tm_hour < 10 ? "0" + std::to_string(5 + ltm->tm_hour) : std::to_string(5 +ltm->tm_hour);
        minute = 30 + ltm->tm_min < 10 ? "0" + std::to_string(30 + ltm->tm_min) : std::to_string(30 + ltm->tm_min);

        itHist->second.insert_or_assign(hour + minute, e);
    }
}

template<isChar U> void Communicator::AcquireData(U* data[], int dataSize)
{
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
    }

    for (std::array dataArr = std::to_array<char*>(data); auto &e : dataArr)
    {
        hour = 5 + ltm->tm_hour < 10 ? "0" + std::to_string(5 + ltm->tm_hour) : std::to_string(5 +ltm->tm_hour);
        minute = 30 + ltm->tm_min < 10 ? "0" + std::to_string(30 + ltm->tm_min) : std::to_string(30 + ltm->tm_min);

        itHist->second.insert_or_assign(hour + minute, static_cast<uint32_t>(e));
    }
}

template<isVector U> void Communicator::AcquireData(U* data)
{
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
    }

    for (auto &e : data)
    {
        hour = 5 + ltm->tm_hour < 10 ? "0" + std::to_string(5 + ltm->tm_hour) : std::to_string(5 +ltm->tm_hour);
        minute = 30 + ltm->tm_min < 10 ? "0" + std::to_string(30 + ltm->tm_min) : std::to_string(30 + ltm->tm_min);

        itHist->second.insert_or_assign(hour + minute, e);
    }
}

#else
void Communicator::AcquireData(uint32_t* uData, int dataSize)
{
    for (int i = 0; i < dataSize; i++)
    {
        *vIt = uData[i];
        vIt++;
        if (vIt == vBuffer.end())
            vIt = vBuffer.begin();
    }
}

void Communicator::AcquireData(char* cData[], int dataSize)
{
    for (int i = 0; i < dataSize; i++)
    {
        *vIt = static_cast<uint32_t>(*cData[i]);
        vIt++;
        if (vIt == vBuffer.end())
            vIt = vBuffer.begin();
    }
}

void Communicator::AcquireData(std::vector<uint32_t>* vData)
{
    for (auto &value : *vData)
    {
        *vIt = value;
        vIt++;
        if (vIt == vBuffer.end())
            vIt = vBuffer.begin();
    }
}
#endif

void Communicator::Start()
{
    sRunState = State::Running;

    while (sRunState == State::Running)
    {
        CommuteData();
    }
}

template<typename T> void Communicator::AcquireData(T* tData, int dataSize)
{
    if (std::is_integral_v<T> && std::is_unsigned_v<T>)
        AcquireData(static_cast<uint32_t*>(tData), dataSize);
    else if (std::is_same_v<T, char>)
        AcquireData(static_cast<char**>(tData), dataSize);
    else if (std::is_array_v<T>)
        AcquireData(static_cast<std::vector<uint32_t>*>(tData));
}

void Communicator::FlushBuffer()
{
    vBuffer.clear();
    vIt = vBuffer.begin();
}

template<typename U> U Communicator::GetSingleData(int position /*= -1*/)
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

template<typename U> size_t Communicator::GetRawBuffer(U* retBuff, int dataSize /*= -1*/)
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

Communicator::~Communicator()
{
    printf("THIS IS COMMUNICATOR ABSTRACTION DESTRUCTOR\n");
}

Receiver::Receiver(int receiverID) : Communicator(receiverID, CommunicatorType::Receiver)
{
    memset(uBuffer, 0, RX_BUFFER);
    uBufferPosition = 0;
    printf("THIS IS RECEIVER CONSTRUCTOR\n");
}

void Receiver::FlushBuffer()
{
    memset(uBuffer, 0, RX_BUFFER);
    uBufferPosition = 0;
    Communicator::FlushBuffer();
}

void Receiver::CommuteData()
{
    for (int i = 0; i < RX_BUFFER; i++)
    {
        uint32_t sendValue = GetSingleData<uint32_t>(uBufferPosition);
        // TODO: Send Data (single vs buffer - look HAL docs)
        uBufferPosition++;
        if (uBufferPosition >= RX_BUFFER)
            uBufferPosition = 0;
    }
}

bool Receiver::HalfCptCallback()
{
    // TODO get HAL callbacks
    if (uBufferPosition >= RX_BUFFER / 2)
        return true;

    return false;
}

bool Receiver::FullCptCallback()
{
    // TODO get HAL callbacks
    if (uBufferPosition >= RX_BUFFER)
        return true;

    return false;
}

Receiver::~Receiver()
{
    printf("THIS IS RECEIVER DESTRUCTOR\n");
}

Transmitter::Transmitter(int receiverID) : Communicator(receiverID, CommunicatorType::Transmitter)
{
    memset(uBuffer, 0, RX_BUFFER);
    uBufferPosition = 0;
    printf("THIS IS TRANSMITTER CONSTRUCTOR\n");
}

void Transmitter::FlushBuffer()
{
    memset(uBuffer, 0, RX_BUFFER);
    uBufferPosition = 0;
    Communicator::FlushBuffer();
}

void Transmitter::CommuteData()
{
    for (int i = 0; i < RX_BUFFER; i++)
    {
        uint32_t sendValue = GetSingleData<uint32_t>(uBufferPosition);
        // TODO: Send Data (single vs buffer - look HAL docs)
        uBufferPosition++;
        if (uBufferPosition >= RX_BUFFER)
            uBufferPosition = 0;
    }
}

bool Transmitter::HalfCptCallback()
{
    if (uBufferPosition >= RX_BUFFER / 2)
        return true;

    return false;
}

bool Transmitter::FullCptCallback()
{
    if (uBufferPosition >= RX_BUFFER)
        return true;

    return false;
}

Transmitter::~Transmitter()
{
    printf("THIS IS TRANSMITTER DESTRUCTOR\n");
}
