#include <iostream>
#include <SFML/Network.hpp>
#include "Utils.h"

#define MAX_DATA_SIZE	10
#define ADDRESS			"192.168.0.2"
#define PORT			4560
#define

int main()
{
	std::string addr = "localhost";
	int port = 4560;

	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(addr, port);

<<<<<<< Updated upstream
	sf::Packet packet;
	std::string serverCommands;
=======
	//char data[100];
	//std::string data[1];
	//unsigned char data[MAX_DATA_SIZE + 1]; //This may work but if not I am going to make a null thing
	//std::size_t received;
	sf::Packet packet;
	std::string data;
>>>>>>> Stashed changes

	try
	{
		if (status != sf::Socket::Done)
		{
			std::cout << "Unable to connect to server " << addr << ":" << port;
		}
		std::cout << "Connected to " << addr << ":" << port << std::endl;

<<<<<<< Updated upstream
		socket.recieve(packet);
		packet >> serverCommands; //This may work with the server who knows
		std::cout << "Data in packet: " << serverCommands;
=======
		//socket.receive(data, MAX_DATA_SIZE + 1, received);
		socket.receive(packet);
		packet >> data;


		std::cout << "Data:" << data << std::endl << "Received:" << "Maybe 3 could be 4" << std::endl;
		//std::cout << "Message hopefully defucked: " << returnCommands(data, received)[1];
>>>>>>> Stashed changes

	}
	catch (const std::exception& e) { std::cout << "Error: " << e.what(); }

	
	return 0;
}
