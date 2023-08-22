#pragma once

#include <WinSock2.h>

class SocketRAII
{
public:
    SocketRAII() : m_sockfd(INVALID_SOCKET) {}
    SocketRAII(SOCKET sockfd) : m_sockfd(sockfd) {}

    ~SocketRAII()
    {
        if (m_sockfd != INVALID_SOCKET)
        {
            closesocket(m_sockfd);
        }
    }

    SOCKET get() const
    {
        return m_sockfd;
    }

    void reset(SOCKET sockfd)
    {
        if (m_sockfd != INVALID_SOCKET)
        {
            closesocket(m_sockfd);
        }
        m_sockfd = sockfd;
    }

    void close()
    {
        if (m_sockfd != INVALID_SOCKET)
        {
            shutdown(m_sockfd, SD_BOTH);
            closesocket(m_sockfd);
            m_sockfd = INVALID_SOCKET;
        }
    }

    SocketRAII(const SocketRAII&) = delete;
    SocketRAII& operator=(const SocketRAII&) = delete;

private:
    SOCKET m_sockfd;
};
