#include <iostream>
#include <SFML/Network.hpp>
#include "Utils.h"
#include <thread>

int main()
{
	std::string hostname = "71.7.242.3";
	int port = 4560;
	
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(hostname, port);

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

		socket.receive(packet);
		packet >> data;

		std::cout << "Data:" << data << std::endl << "Received:" << "Maybe 3 could be 4" << std::endl;
		//experimentalSplit(data, v);
		splitString(data, v);
		processingCommand = true;
		ParseCommand(v);
		std::cout << "VECTOR DATA: " << v.size();
		v.clear();
		data.clear();
		packet.clear();


		//std::thread receivingData (processPacket, socket, packet, data);
		//std::thread processing (doCommandStuff, data, v, processingCommand);

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
			data.clear();
			packet.clear();
		}
		catch (const std::exception& e) { std::cout << "Error: " << e.what(); }
		*/
	}
	
	return 0;
}
