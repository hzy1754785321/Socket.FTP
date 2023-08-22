#pragma once
#include <memory>
#include "Common.h"
#include "DataStructures.h"
#include "Socket.h"

class SocketDispatcher{
public:
    SocketDispatcher(int protocolType);

    static SocketDispatcher& GetInstance(int protocolType)
    {
        static SocketDispatcher instance(protocolType);
        return instance;
    }

    bool Connect(NetAddress address);
    void DisConnect();
    bool Receive();
    bool Send();
    bool IsConnect() const;
    int GetConnectState() const;

private:
    std::unique_ptr<SocketManager> socketManager;
};