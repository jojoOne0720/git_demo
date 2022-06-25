#ifndef _BUFFER_H
#define _BUFFER_H
#include "disposable.h"
class CBuffer:public CDisposable
{
public:
    virtual unsigned int getCanWriteSize();
    //如果buffer的长度不够，该函数会自动增长长度
    int reallocBuffer() {return 0;}; 

    virtual void Dispose();
protected:
    //指向buffer的指针
    char* m_buffer;
    //buffer开始位
    unsigned int m_bufferbegin;
    //buffer结束位
    unsigned int m_bufferend;
    //buffer总长度
    unsigned int m_bufferlenght;
};

#endif