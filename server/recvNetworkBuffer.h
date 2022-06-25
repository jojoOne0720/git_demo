#ifndef _RECV_NETWORK_BUFFER_H_
#define _RECV_NETWORK_BUFFER_H_
#include "networkBuffer.h"
class CRecvNetworkBuffer : public CNetworkBuffer
{
public:
    CRecvNetworkBuffer(unsigned int size):CNetworkBuffer(size) {}
    //获取数据头地址
    int getBuffer(char *&buffer);
};

#endif