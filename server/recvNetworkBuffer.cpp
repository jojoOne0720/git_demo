#include "recvNetworkBuffer.h"

int CRecvNetworkBuffer::getBuffer(char *&buffer)
{
    buffer = m_buffer;
    return getCanWriteSize();
}