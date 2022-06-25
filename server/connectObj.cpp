#include "connectObj.h"


bool CConnectObj::recvBuffer()
{
    char* buf = nullptr;
    while(true)
    {
        //判断如果程序缓存区空间不够，自动增长
        if(m_recvBuff.getCanReadSize())
            m_recvBuff.reallocBuffer();
        const int canReadSize = m_recvBuff.getBuffer(buf);
        int readSize = recv(connect,buf,canReadSize,0);
        if(readSize > 0)
        {
            m_recvBuff.fillDate(readSize);
        }
        else if(readSize == 0)
        {
            return false;
        }
        else 
        {
            std::cout<<"recvBuffer erro"<<std::endl;
            return false;
        }
    }
}