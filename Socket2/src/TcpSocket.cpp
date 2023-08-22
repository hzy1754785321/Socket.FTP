#include "../include/TcpSocket.h"
#include <WinSock2.h>
#include <ws2tcpip.h> 
#include <chrono>
#include <thread>
#include <mutex>
#pragma comment(lib, "ws2_32.lib")

TcpSocketManager::TcpSocketManager()
{
	InitWinsock();
}

TcpSocketManager::~TcpSocketManager()
{
	WSACleanup();
}

void TcpSocketManager::InitWinsock()
{
	static std::once_flag flag;
	std::call_once(flag, [] {
		WSADATA wsaData;
		int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (ret != 0)
		{
			throw std::system_error(ret, std::system_category(), "Failed to initialize Winsock");
		}
		});
}


bool TcpSocketManager::Connect(NetAddress address)
{
	m_sockfd.reset(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP));
	if (m_sockfd.get() == INVALID_SOCKET)
	{
		return false;
	}

	struct sockaddr_in serverAddr {};
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(address.port);
	inet_pton(AF_INET, address.ip.c_str(), &serverAddr.sin_addr);

	//设置重试次数为3,每次重试等待1秒
	for (int tryCount = 0; tryCount < 3; ++tryCount)
	{
		if (connect(m_sockfd.get(), (sockaddr*)&serverAddr, sizeof(serverAddr)) != SOCKET_ERROR)
		{
			//设为堵塞模式
			u_long argp = 0; // 0: 阻塞, 1: 非阻塞
			ioctlsocket(m_sockfd.get(), FIONBIO, &argp);
			int timeout = 5000; //超时时间设为5秒
			setsockopt(m_sockfd.get(), SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
			return true;
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	return false;
}

int TcpSocketManager::GetConnectState()
{
	if (m_sockfd.get() == INVALID_SOCKET)
	{
		return SOCKET_STATE_DISCONNECTED;
	}

	fd_set fdread{}, fdwrite{}, fdexcep{};
	FD_ZERO(&fdread);
	FD_ZERO(&fdwrite);
	FD_ZERO(&fdexcep);
	FD_SET(m_sockfd.get(), &fdread);
	FD_SET(m_sockfd.get(), &fdwrite);
	FD_SET(m_sockfd.get(), &fdexcep);

	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 0;

	int ret = select(0, &fdread, &fdwrite, &fdexcep, &tv);
	if (ret == SOCKET_ERROR)
	{
		return SOCKET_STATE_ERROR;
	}
	else if (ret == 0)
	{
		return SOCKET_STATE_CONNECTED;
	}
	else
	{
		if (FD_ISSET(m_sockfd.get(), &fdread))
		{
			return SOCKET_STATE_READABLE;
		}
		else if (FD_ISSET(m_sockfd.get(), &fdwrite))
		{
			return SOCKET_STATE_WRITABLE;
		}
		else if (FD_ISSET(m_sockfd.get(), &fdexcep))
		{
			return SOCKET_STATE_ERROR;
		}
	}
	return SOCKET_STATE_UNKNOWN;
}

bool TcpSocketManager::IsConnect() const
{
	if (m_sockfd.get() == INVALID_SOCKET)
	{
		return false;
	}

	int error = 0;
	int len = sizeof(error);
	int ret = getsockopt(m_sockfd.get(), SOL_SOCKET, SO_ERROR, (char*)&error, &len);
	if (ret == SOCKET_ERROR || error != 0)
	{
		return false;
	}

	return true;
}

bool TcpSocketManager::Send() const
{
	return false;
}

bool TcpSocketManager::Receive() const
{
	return false;
}

void TcpSocketManager::DisConnect()
{
	m_sockfd.close();
}