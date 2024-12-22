//
//  communicators.hpp
//  plants_watersystem
//
//  Created by Piotr Cieślik on 17/12/24.
//

#ifndef communicators_hpp
#define communicators_hpp

#include "device.hpp"
#include "globals.hpp"

class Communicator : public Device<CommunicatorType>
{
private:
    std::vector<uint32_t> vBuffer;
    std::vector<uint32_t>::iterator vIt;
#if 0
    template<isUint U> void AcquireData(U* data, int dataSize);
    template<isChar U> void AcquireData(U* data[], int dataSize);
    template<isVector U> void AcquireData(U* data);
#else
    void AcquireData(uint32_t* uData, int dataSize);
    void AcquireData(char* cData[], int dataSize);
    void AcquireData(std::vector<uint32_t>* vData);
#endif
public:
    Communicator(int communicatorID, CommunicatorType communicatorType);
    virtual void Start();
    virtual void CommuteData() = 0;
    virtual void FlushBuffer();
    virtual bool HalfCptCallback() = 0;
    virtual bool FullCptCallback() = 0;
    template<typename T> void AcquireData(T* tData, int dataSize);
    template<typename U> U GetSingleData(int position = -1);
    template<typename U> size_t GetRawBuffer(U* retBuff, int dataSize = - 1);
    ~Communicator();
};

class Receiver : public Communicator
{
private:
    uint32_t uBuffer[RX_BUFFER];
    int uBufferPosition;
public:
    Receiver(int receiverID);
    virtual void FlushBuffer() override;
    virtual void CommuteData() override;
    virtual bool HalfCptCallback() override;
    virtual bool FullCptCallback() override;
    ~Receiver();
};

class Transmitter : public Communicator
{
private:
    uint32_t uBuffer[TX_BUFFER];
    int uBufferPosition;
public:
    Transmitter(int receiverID);
    virtual void FlushBuffer() override;
    virtual void CommuteData() override;
    virtual bool HalfCptCallback() override;
    virtual bool FullCptCallback() override;
    int GetBuffer(uint32_t* uInpBuffer, int inputBufferSize);
    ~Transmitter();
};

#endif /* communicators_hpp */
