#include <iostream>
#include <SFML/Network.hpp>
#include "Utils.h"

#define MAX_DATA_SIZE	10
#define ADDRESS			"192.168.0.2"
#define PORT			4560
#define

int main()
{
	std::string addr = "192.168.0.2";
	int port = 4560;

	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(addr, port);

	sf::Packet packet;
	std::string serverCommands;

	try
	{
		if (status != sf::Socket::Done)
		{
			std::cout << "Unable to connect to server " << addr << ":" << port;
		}
		std::cout << "Connected to " << addr << ":" << port << std::endl;

		socket.recieve(packet);
		packet >> serverCommands; //This may work with the server who knows
		std::cout << "Data in packet: " << serverCommands;

	}
	catch (const std::exception& e) { std::cout << "Error: " << e.what(); }

	
	return 0;
}
