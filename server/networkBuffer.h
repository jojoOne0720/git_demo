#ifndef _NETWORK_BUFFER_H_
#define _NETWORK_BUFFER_H_
#include "buffer.h"

//用short接收一条协议数据的总长度
typedef short onePackLenght; 

struct SPackHead
{
    unsigned short head;
};

class CNetworkBuffer:public CBuffer
{
public:
    explicit CNetworkBuffer(const unsigned int size);
    virtual ~CNetworkBuffer();
    //判断是否有一个协议头的长度
    bool HasData() const;

    //获取可写长度
	unsigned int getCanWriteSize() override;
    //获取可读长度
    unsigned int getCanReadSize();
    
    void fillDate(unsigned int  size);

    //去除数据
    void removeDate(unsigned int size);
protected:
    //真实数据长度（使用环形方式接收数据）
    unsigned int m_realSize;
};

#endif