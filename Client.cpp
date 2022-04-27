#include <iostream>
#include <SFML/Network.hpp>
#include "Utils.h"

#define MAX_DATA_SIZE 10

int main()
{
	std::string addr = "192.168.0.2";
	int port = 4560;

	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(addr, port);

	//char data[100];
	//std::string data[1];
	unsigned char data[MAX_DATA_SIZE + 1]; //This may work but if not I am going to make a null thing
	std::size_t received;

	try
	{
		if (status != sf::Socket::Done)
		{
			std::cout << "Unable to connect to server " << addr << ":" << port;
		}
		std::cout << "Connected to " << addr << ":" << port << std::endl;

		socket.receive(data, MAX_DATA_SIZE + 1, received);

		std::cout << "Data:" << data << std::endl << "Received:" << received << std::endl;
		//std::cout << "Message hopefully defucked: " << returnCommands(data, received)[1];

	}
	catch (const std::exception& e) { std::cout << "Error: " << e.what(); }

	
	return 0;
}
