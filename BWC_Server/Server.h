#pragma once
#include "iostream"
#include "vector"

#include "WinSock2.h"
#include "WS2tcpip.h"

#pragma comment(lib, "Ws2_32.lib")

namespace bwc_n
{

	class Server
	{

		WSADATA wsaData;

		SOCKET Socket;

		in_addr IPToNum;

		sockaddr_in info;

		int erStat;

		//Server info
		const char* IP;
		int PORT;
		short BUFF_DATA_SIZE;

		std::vector<SOCKET> clients;

		void init();

	public:
		Server();
		Server(const char* ip);

		void work();

	};

}
