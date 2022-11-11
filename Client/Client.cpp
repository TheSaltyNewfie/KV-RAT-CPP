#include <iostream>
#include <SFML/Network.hpp>
#include "Utils.h"
#include "ScreenCapture.h"
#include <thread>

struct{
	std::string hostname = "127.0.0.1";
	int port = 4560;
} config;

struct {
	int videom = 1;
	int console = 2;
	int diag = 3;
} modes;

int main()
{
	sf::TcpSocket socket;

	sf::Socket::Status status = socket.connect(config.hostname, config.port);

	sf::Packet lpacket;
	sf::Packet wpacket;
	std::string data;
	std::vector<std::string> v;

	if (status != sf::Socket::Done)
		std::cout << "Unable to connect to any servers on your defined values";
	std::cout << "\nConnected!" << "\nDEV: " << config.hostname << ":" << config.port;

	Sleep(5000);

	while (true)
	{
		Sleep(22);

		std::cout << "22ms reached! sending screenshots!";
		lpacket << GetScreenShot();
		socket.send(lpacket);

		socket.receive(wpacket);
		wpacket >> data;
		StringUtils::experimentalSplit(data, v);
		ParseCommand(v);

		lpacket.clear();
		wpacket.clear();
		data.clear();
		v.clear();
		


		/*
		socket.receive(packet);
		std::cout << "\nDEV: PACKET RECV";

		packet >> data;
		std::cout << "\nDEV: PACKET INFO: " << packet.getData();
		std::cout << "\nDEV: DATA: " << data;

		StringUtils::experimentalSplit(data, v);
		std::cout << "\nDEV: SHIT SPLIT";

		ParseCommand(v);
		std::cout << "\nDEV: PARSED!";

		packet.clear();
		data.clear();
		std::cout << "\nDEV: DATA AND PACKET CLEARED!" << "\nDATA: " << data << "\nPACKET: " << packet.getData();
		*/
	}




	/*s
	try
	{
		while (true)
		{
			sf::Tcplm_socket lm_socket;
			sf::lm_socket::Status status = lm_socket.connect(config.hostname, config.port);

			if (status != sf::lm_socket::Done)
			{
				std::cout << "Unable to connect to server " << config.hostname << ":" << config.port;
			}
			std::cout << "Connected to " << config.hostname << ":" << config.port << std::endl;

			while (true)
			{
				lm_socket.receive(packet);
				packet >> data;
				StringUtils::experimentalSplit(data, v);
				ParseCommand(v);
				std::cout << "\nWe parsed some shit = " << data << "\n";
				packet.clear();
			}
		}
	}
	catch (std::exception& e) { std::cout << "COVERING ALL: " << e.what(); }
	
	
	while (true)
	{
		if (status != sf::lm_socket::Done)
			std::cout << "Unable to connect to server " << hostname << ":" << port;
		std::cout << "Connected to " << hostname << ":" << port << std::endl;
		isConnected = true;


		lm_socket.receive(packet);
		packet >> data;

		//std::cout << "Data:" << data << std::endl << "Received:" << "Maybe 3 could be 4" << std::endl;
		//experimentalSplit(data, v);
		experimentalSplit(data, v);
		processingCommand = true;
		ParseCommand(v);
		debugData.lastReceived = data;
		std::cout << debugData.lastReceived;
		v.clear();
		data.clear();
		packet.clear();
	}
	*/
	return 0;
}
