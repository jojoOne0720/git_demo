#ifndef _NETWORK_H_
#define _NETWORK_H_
#include <sys/select.h>
#include <fcntl.h>
#include "connectObj.h"
class CNetwork:public CDisposable
{
public:
    CNetwork();
    virtual ~CNetwork();
    bool socketInit();
    bool Select();
    bool Recv(int connect, char* buf,int& len);
    bool Send(int connect, const char* buf, int& iLen);

    void SetSocketOpt(int socket);
    virtual void Dispose();
protected:
    fd_set* socketSet;
    fd_set* readSet;
    fd_set* writeSet;
    
    int m_mysocket;
    std::map<int,ConnectObjPtr> m_connect;
};

#endif
