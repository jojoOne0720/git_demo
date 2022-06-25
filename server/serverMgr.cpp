#include "serverMgr.h"

void CServerMgr::serverInit()
{
    Listen();
}


void CServerMgr::handlePack()
{ 
    for(auto connect = m_connect.begin(); connect != m_connect.end(); ++connect)
    {
        connect->second->canReadPack();
    }
}