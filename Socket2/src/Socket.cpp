#include "../include/Socket.h"
#include <WinSock2.h>
#include <ws2tcpip.h> 
#include <chrono>
#include <thread>
#include <mutex>

//SocketManager::SocketManager()
//{
//	InitWinsock();
//}
//
//SocketManager::~SocketManager()
//{
//	WSACleanup();
//}

bool SocketManager::Connect(NetAddress address)
{
	return false;
}

bool SocketManager::Send() const
{
	return false;
}

bool SocketManager::Receive() const
{
	return false;
}

void SocketManager::DisConnect()
{

}

int SocketManager::GetConnectState()
{
	return 0;
}
