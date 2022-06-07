#include <iostream>
#include <SFML/Network.hpp>
#include "Utils.h"
#include <thread>

int main(int argc, char* argv)
{
	std::string hostname = argv[0];
	int port = argv[1];
	
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(addr, port);

	sf::Packet packet;
	std::string data;
	std::vector<std::string> v;

	std::vector<std::string> commandBuffer;
	int bufferSize = sizeof(commandBuffer);
	bool processingCommand = false;

	while (true)
	{
		if (status != sf::Socket::Done)
			std::cout << "Unable to connect to server " << hostname << ":" << port;
		std::cout << "Connected to " << hostname << ":" << port << std::endl;

		std::thread receivingData (processPacket, socket, packet, data);
		std::thread processing (doCommandStuff, data, v, processingCommand);

		/*
		try
		{
			if (status != sf::Socket::Done)
			{
				std::cout << "Unable to connect to server " << addr << ":" << port;
			}
			std::cout << "Connected to " << addr << ":" << port << std::endl;

			socket.receive(packet);
			packet >> data;

			std::cout << "Data:" << data << std::endl << "Received:" << "Maybe 3 could be 4" << std::endl;
			splitString(data, v);
			processingCommand = true;
			ParseCommand(v);
			v.clear();
		}
		catch (const std::exception& e) { std::cout << "Error: " << e.what(); }
		*/
	}
	
	return 0;
}
