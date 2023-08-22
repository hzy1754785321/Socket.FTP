#include "../include/SocketDispatcher.h"
#include "../include/TcpSocket.h"
#include "../include/UdpSocket.h"

SocketDispatcher::SocketDispatcher(int protocolType)
{
    ProtocolType type = static_cast<ProtocolType>(protocolType);
    switch (type)
    {
    case ProtocolType::TcpSocketManager:
        socketManager = std::make_unique<TcpSocketManager>();
        break;
    case ProtocolType::UdpSocketManager:
        //  socketManager = std::make_unique<UdpSocketManager>();
        break;
    default:
        socketManager = std::make_unique<TcpSocketManager>();
        break;
    }
}


bool SocketDispatcher::Connect(NetAddress address) 
{
    return socketManager->Connect(address);
}

void SocketDispatcher::DisConnect()
{
    socketManager->DisConnect();
}

bool SocketDispatcher::Receive() 
{
    return socketManager->Receive();
}

bool SocketDispatcher::Send() 
{
    return socketManager->Send();
}

bool SocketDispatcher::IsConnect() const 
{
    return socketManager->IsConnect();
}

int SocketDispatcher::GetConnectState() const 
{
    return socketManager->GetConnectState();
}