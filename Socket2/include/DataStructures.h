#pragma once
#include <string>

struct NetAddressInterop
{
	const char* ip;
	int port;
};

struct NetAddress
{
	std::string ip;
	int port;
};
