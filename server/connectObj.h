#ifndef _CONNECT_OBJ_H_
#define _CONNECT_OBJ_H_
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "recvNetworkBuffer.h"

class CConnectObj
{
public:
    CConnectObj(int socket) : connect(socket),m_recvBuff(4096) {}
    bool canSendPack() { return false; }
    //判断网络缓存区是否有数据可读
    bool canReadPack() { return m_recvBuff.getCanReadSize(); }

    //接收数据到网络缓冲区
    bool recvBuffer();

private:
    int connect;
    CRecvNetworkBuffer m_recvBuff;
};
typedef std::shared_ptr<CConnectObj> ConnectObjPtr;
#endif