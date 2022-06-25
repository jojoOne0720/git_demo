#ifndef _DISPOSABLE_H_
#define _DISPOSABLE_H_
#include <arpa/inet.h>
#include <sys/socket.h>
class CDisposable
{
public:
    virtual ~CDisposable() = default;
    virtual void Dispose() = 0;

};



#endif 