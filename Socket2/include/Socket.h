#pragma once

#include <string>
#include "SocketRAII.h"
#include "Common.h"

class SocketManager {
public:
	SocketManager() = default;
	~SocketManager() = default;

	virtual bool Connect(NetAddress address) = 0;
	virtual void DisConnect() = 0;
	virtual bool Receive() const = 0;
	virtual bool Send() const = 0;
	virtual bool IsConnect() const = 0;
	virtual int GetConnectState() = 0;
	SocketManager(const SocketManager&) = delete;
	SocketManager& operator=(const SocketManager&) = delete;
};