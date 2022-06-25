#include "serverMgr.h"

int main()
{
    CServerMgr server;

    server.Listen();
    while (true)
    {
        if (!server.Update())
            break;
        server.handlePack();
    }
    server.Dispose();
    return 0;
}