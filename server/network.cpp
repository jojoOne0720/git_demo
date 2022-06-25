#include "network.h"

CNetwork::CNetwork() : m_mysocket(-1)
{
    m_connect.clear();
    socketSet = new fd_set();
    readSet = new fd_set();
    writeSet = new fd_set();
    if (nullptr == socketSet || nullptr == readSet || nullptr == writeSet)
    {
        std::cout << "socketSet error" << std::endl;
    }
}

CNetwork::~CNetwork()
{
    Dispose();
}

bool CNetwork::socketInit()
{
    this->m_mysocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    unsigned long ul = 1;
    // int ret=ioctlsocket(this->m_mysocket, FIONBIO, (unsigned long *)&ul);//设置成非阻塞模式。

    int flags = fcntl(this->m_mysocket, F_GETFL, 0);

    int ret = fcntl(this->m_mysocket, F_SETFL, flags | O_NONBLOCK);

    if (ret == -1)
    {
        std::cout << "Socket fcntl error" << std::endl;
        return false;
    }
    // if(ret==SOCKET_ERROR)//设置失败
    // {

    // }
    // if (this->m_mysocket == INVALID_SOCKET)
    // {
    // 	std::cout << "Socket error" << std::endl;
    // }
    return true;
}

bool CNetwork::Recv(int connect, char *buf, int &len)
{
    len = recv(connect, buf, 1024, 0);
    return len;
}

bool CNetwork::Send(int connect, const char *buf, int &iLen)
{
    if (send(connect, buf, iLen, 0) < 0)
    {
        std::cout << "ServerSend Error" << std::endl;
        return false;
    }
    return true;
}

bool CNetwork::Select()
{
    //把集合的socket清空，防止断开的socket还保留在集合中
    FD_ZERO(socketSet);
    FD_ZERO(readSet);
    FD_ZERO(writeSet);

    FD_SET(m_mysocket, socketSet);
    FD_SET(m_mysocket, readSet);
    FD_SET(m_mysocket, writeSet);

    //遍历连接的socket，放到集合中
    for (std::map<int, ConnectObjPtr>::iterator it = m_connect.begin(); it != m_connect.end(); ++it)
    {
        FD_SET(it->first, socketSet);
        FD_SET(it->first, readSet);
        if (it->second->canSendPack())
        {
            FD_SET(it->first, writeSet);
        }
    }

    timeval time = {0, 5000};
    //同时检查套接字的可读可写性。
    int nRetAll = select(0, readSet, writeSet, socketSet, &time); //若不设置超时则select为阻塞
    if (nRetAll > 0)
    {
        //判断该socket是否有错误,有就从connect中去掉
        for (auto it = m_connect.begin(); it != m_connect.end();)
        {
            if (FD_ISSET(it->first, socketSet))
                m_connect.erase(it++);
            else
                ++it;
        }

        // 判断是否可读
        for (std::map<int, ConnectObjPtr>::iterator it = m_connect.begin(); it != m_connect.end(); ++it)
        {
            if (FD_ISSET(it->first, readSet) && it->first != this->m_mysocket)
            {
                it->second->recvBuffer();
            }
        }

        for (std::map<int, ConnectObjPtr>::iterator it = m_connect.begin(); it != m_connect.end(); ++it)
        {
            if (FD_ISSET(it->first, writeSet))
            {
                //把监听socket从可写集合中去掉
                if (it->first == this->m_mysocket)
                    FD_CLR(it->first, writeSet);
                //把程序发送缓存区的数据放到socket发送缓存区中
            }
        }
    }
    return true;
}

void CNetwork::SetSocketOpt(int socket)
{
    bool addr = true;
    setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (const char *)&addr, sizeof(addr));

    int netTimeout = 3000;
    setsockopt(socket, SOL_SOCKET, SO_SNDTIMEO, (const char *)&netTimeout, sizeof(netTimeout));
    // setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&netTimeout, sizeof(netTimeout));
    // unsigned long ul=1;
    // int ret=fcntl(socket, FIONBIO, (unsigned long *)&ul);//设置成非阻塞模式。

    int flags = fcntl(socket, F_GETFL, 0);
    int ref = fcntl(socket, F_SETFL, flags | O_NONBLOCK);
    if (ref == -1)
    {
        std::cout << "ioctlsocket erro" << std::endl;
    }
    // if(ret==SOCKET_ERROR)//设置失败
    // {
    //     std::cout<<"ioctlsocket erro"<<std::endl;
    // }
}

void CNetwork::Dispose()
{
    delete socketSet;
    delete readSet;
    delete writeSet;
    socketSet = nullptr;
    readSet = nullptr;
    writeSet = nullptr;
}