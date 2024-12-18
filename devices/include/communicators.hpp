//
//  communicators.hpp
//  plants_watersystem
//
//  Created by Piotr Cieślik on 17/12/24.
//

#ifndef communicators_hpp
#define communicators_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include "device.hpp"
#include "globals.hpp"

class Communicator : public Device<CommunicatorType>
{
private:
    std::map<std::string, std::map<std::string, uint32_t>> historyData;
    std::map<std::string, std::map<std::string, uint32_t>>::iterator itHist;
    std::map<std::string, uint32_t>::iterator itTimed;

    void AcquireData(uint32_t* data, int dataSize);
    void AcquireData(char* data[], int dataSize);
    void AcquireData(std::vector<uint32_t>* data);
public:
    Communicator(int communicatorID, CommunicatorType communicatorType);
    virtual void Start();
    virtual void FlushBuffer();
    virtual void CommuteData() = 0;
    virtual bool HalfCptCallback() = 0;
    virtual bool FullCptCallback() = 0;

    template<typename T> void AcquireData(T* data, int dataSize);
    void AcquireHistoryData(std::map<std::string, std::map<std::string, uint32_t>> historyData);
    void AcquireTimedData(std::map<std::string, uint32_t> timedData, std::string date);
    void AcquireSingleData(std::string date, std::string time, uint32_t data);

    ~Communicator();
};

class Receiver : public Communicator
{
private:
    uint32_t buffer[RX_BUFFER];
    int bufferPosition;
public:
    Receiver(int receiverID);

    virtual void CommuteData() override;
    virtual bool HalfCptCallback() override;
    virtual bool FullCptCallback() override;

    ~Receiver();
};

class Transmitter : public Communicator
{
private:
    uint32_t buffer[TX_BUFFER];
    int bufferPosition;
public:
    Transmitter(int receiverID);

    virtual void CommuteData() override;
    virtual bool HalfCptCallback() override;
    virtual bool FullCptCallback() override;

    ~Transmitter();
};

#endif /* communicators_hpp */
