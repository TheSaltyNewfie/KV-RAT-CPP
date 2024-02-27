#include "networking.h"
const int DEFAULT_PORT = 4560;
const int BUFFER_SIZE = 4096;
/*
void network::client(char ip[])
{
	std::cout << "Attempting connection to " << ip << "\n";

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cerr << "Failed to init winsock.\n";
		return;
	}

	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET)
	{
		std::cerr << "Failed to create client socket.\n";
		WSACleanup();
		return;
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
		return;
	}

	std::cout << "Connected to server.\n";

	while (true)
	{
		std::string recv = receiveData(clientSocket);
		if (recv.empty())
		{
			std::cout << "Server disconnected.\n";
			break;
		}
		
		if (recv == "Screenshot")
		{
			std::cout << "Sending screenshot.\n";
			std::vector<char> imageData = commands::Screenshot_C();
			std::cout << "DATA: " << imageData.size() << " bytes.\n";
			int bytes_sent = send(clientSocket, imageData.data(), imageData.size(), 0);
			send(clientSocket, "EOF", 3, 0);
			std::cout << "Screenshot Sent.\n";
		}
		else
		{
			std::vector<std::string> cleaning = CommandHandler::cleanFunctions(recv);
			CommandHandler::callFunction(cleaning);

			sendData(clientSocket, "command received.\n");

			std::cout << "Server: " << recv << "\n";

			cleaning.clear();
			recv.clear();
		}
	}

	closesocket(clientSocket);
	WSACleanup();
}
*/

struct packet
{
	std::string command;
	std::string information;
	int mx;
	int my;
};

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

	while(true)
	{
		//Receive data from the server
		nlohmann::json data = networking::recvData(clientSocket);
		packet np{
			data["command"].template get<std::string>(),
			data["information"].template get<std::string>(),
			0,
			0
		};

		//Check for information before we do anything, e.g. server shutting down
		//auto information = data["information"].template get<std::string>();
		if(np.information == "Shutdown")
		{
			closesocket(clientSocket);
			WSACleanup();
			exit(0);
		}

		std::string test = data.dump(4);

		printf("%s", test.c_str());
	}

	return 0;
}