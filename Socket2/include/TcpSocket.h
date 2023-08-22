#pragma once
#include "SocketRAII.h"
#include "DataStructures.h"
#include "Socket.h"

class TcpSocketManager : public SocketManager {
public:
	TcpSocketManager();
	~TcpSocketManager();

	bool Connect(NetAddress address);
	void DisConnect();
	bool Receive() const;
	bool Send() const; 
	bool IsConnect() const;
	int GetConnectState();

	TcpSocketManager(const SocketManager&) = delete;
	TcpSocketManager& operator=(const SocketManager&) = delete;
private:
	static void InitWinsock();
	SocketRAII m_sockfd;
};