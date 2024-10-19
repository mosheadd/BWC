#include "Server.h"


namespace bwc_n
{

	Server::Server()
	{

		IP = "127.0.0.1";

		init();

	}

	Server::Server(const char* ip)
	{

		IP = ip;

		init();

	}

	void Server::init()
	{

		PORT = 1234;
		BUFF_DATA_SIZE = 1024;

		std::cout << "Translating IP to numeric format...\n";

		erStat = inet_pton(AF_INET, IP, &IPToNum);

		if (erStat <= 0)
		{
			std::cout << "Error\n";
			return;
		}
		else std::cout << "OK\n";

		std::cout << "WinSock initialization...\n";

		erStat = WSAStartup(MAKEWORD(2, 2), &wsaData);

		if (erStat != 0)
		{
			std::cout << "Error version #" << WSAGetLastError();
			return;
		}
		else std::cout << "OK\n";

		std::cout << "Socket initialization...\n";

		Socket = socket(AF_INET, SOCK_STREAM, 0);

		if (Socket == INVALID_SOCKET)
		{
			std::cout << "Error. Socket #" << WSAGetLastError() << std::endl;
			closesocket(Socket);
			WSACleanup();
			return;
		}
		else std::cout << "OK\n";

		std::cout << "Server info initialization...\n";

		ZeroMemory(&info, sizeof(info));

		info.sin_family = AF_INET;
		info.sin_addr = IPToNum;
		info.sin_port = htons(PORT);

		std::cout << "Binding...\n";

		erStat = bind(Socket, (sockaddr*)&info, sizeof(info));

		if (erStat != 0)
		{
			std::cout << "Error #" << WSAGetLastError() << std::endl;
			closesocket(Socket);
			WSACleanup();
			return;
		}
		else std::cout << "OK";

	}

	void Server::work()
	{

		closesocket(Socket);

		for (SOCKET client : clients)
			closesocket(client);

		WSACleanup();

	}

}
