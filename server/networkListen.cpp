#include "networkListen.h"
#include "connectObj.h"
bool CNetworkListen::Bind()
{
    if (!socketInit())
    {
        return false;
    }
    int iPort = 98888;
    std::string IP = "127.0.0.1";
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_port = htons(iPort);
    inet_pton(AF_INET, IP.c_str(), &service.sin_addr);
    if (bind(m_mysocket, (sockaddr *)&service, sizeof(service)) == -1)
    {
        std::cout << "Bind error" << std::endl;
    }
    return true;
}

bool CNetworkListen::Listen()
{
    Bind();
    int bocklog = 10;
    if (listen(m_mysocket, bocklog) == -1)
    {
        std::cout << "Listen error" << std::endl;
        return false;
    }
    return true;
}

void CNetworkListen::Accept()
{
    sockaddr_in peer_addr;

    socklen_t iLen = sizeof(peer_addr);
    while (true)
    {
        int connect = accept(m_mysocket, (sockaddr *)&peer_addr, &iLen);

        // std::cout << "Accept suess:" << int(connect) << std::endl;

        if (connect == -1)
        {
            break;
        }

        SetSocketOpt(connect);

        m_connect.insert(std::make_pair(connect, new CConnectObj(connect)));
    }
}

bool CNetworkListen::Update()
{
    bool rs = Select();
    if (FD_ISSET(m_mysocket, readSet))
    {
        Accept();
    }
    return rs;
}