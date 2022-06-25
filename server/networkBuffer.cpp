#include "networkBuffer.h"

CNetworkBuffer::CNetworkBuffer(unsigned int size)
{
    m_bufferlenght = size;
    m_bufferbegin = 0;
    m_bufferend = 0;
    m_realSize = 0;
    m_buffer = new char[m_bufferlenght];
}

CNetworkBuffer::~CNetworkBuffer()
{
    if (nullptr != m_buffer)
    {
        delete[] m_buffer;
        m_buffer = nullptr;
    }
}

bool CNetworkBuffer::HasData() const
{
    //判断是否有真正有意义的数据
    if (m_realSize < 0)
        return false;
    //
    if (m_realSize < (sizeof(onePackLenght) + sizeof(onePackLenght)))
        return false;

    return true;
}

unsigned int CNetworkBuffer::getCanWriteSize()
{
    return m_bufferlenght - m_realSize;
}

unsigned int CNetworkBuffer::getCanReadSize()
{
    return m_realSize;
}

void CNetworkBuffer::fillDate(unsigned int size)
{
    m_realSize += size;
    if (m_bufferlenght - m_bufferend <= size)
    {
        size -= m_bufferlenght - m_bufferend;
        m_bufferend = 0;
    }
    m_bufferend -= size;
}

void CNetworkBuffer::removeDate(unsigned int size)
{
    m_realSize -= size;
    if (m_bufferlenght - m_bufferbegin <= size)
    {
        size -= m_bufferlenght - m_bufferbegin;
        m_bufferbegin = 0;
    }
    m_bufferbegin += size;
}