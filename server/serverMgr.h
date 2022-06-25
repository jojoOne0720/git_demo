#ifndef _SERVER_MGR_H
#define _SERVER_MGR_H
#include "networkListen.h"

class CServerMgr : public CNetworkListen
{
public:
    CServerMgr() {}
    ~CServerMgr() {}

public:
    void serverInit();
    void handlePack();
};

#endif