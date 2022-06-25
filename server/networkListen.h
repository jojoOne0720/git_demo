#ifndef _NETWORK_LISTEN_H_
#define _NETWORK_LISTEN_H_
#include "network.h"

class CNetworkListen:public CNetwork
{
public:
    CNetworkListen() {}
    virtual ~CNetworkListen() {}

    bool Bind();

    bool Listen();

    void Accept();

    bool Update();
};

#endif