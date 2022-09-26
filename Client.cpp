#include <iostream>
#include <SFML/Network.hpp>
#include "Utils.h"
#include <thread>

/*
extern "C"
{
#include "Lua542/include/lua.h"
#include "Lua542/include/lauxlib.h"
#include "Lua542/include/lualib.h"
}

#ifdef _WIN32
#pragma comment(lib, "lua542/liblua54.a")
#endif
*/

struct{
	std::string hostname = "127.0.0.1";
	int port = 4560;
} config;

int main()
{
	sf::Packet packet;
	std::string data;
	std::vector<std::string> v;

	sf::Packet statusData;

	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(config.hostname, config.port);

	if (status != sf::Socket::Done)
		std::cout << "Unable to connect to any servers on your defined values";
	std::cout << "Connected!\n" << "DEV: " << config.hostname << ":" << config.port;

	while (true)
	{
		socket.receive(packet);
		std::cout << "DEV: PACKET RECV\n";

		packet >> data;
		std::cout << "DEV: PACKET INFO: " << data << "\n";

		StringUtils::experimentalSplit(data, v);
		std::cout << "DEV: SHIT SPLIT\n";

		std::cout << "DEV: VECTOR INFO: " << v.data() << "\n";

		ParseCommand(v);
		std::cout << "DEV: PARSED!";

		packet.clear();
		data.clear();
		std::cout << "DEV: DATA AND PACKET CLEARED!\n" << "DATA: " << data << "\nPACKET: " << packet.getData();
	}




	/*s
	try
	{
		while (true)
		{
			sf::TcpSocket socket;
			sf::Socket::Status status = socket.connect(config.hostname, config.port);

			if (status != sf::Socket::Done)
			{
				std::cout << "Unable to connect to server " << config.hostname << ":" << config.port;
			}
			std::cout << "Connected to " << config.hostname << ":" << config.port << std::endl;

			while (true)
			{
				socket.receive(packet);
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
		if (status != sf::Socket::Done)
			std::cout << "Unable to connect to server " << hostname << ":" << port;
		std::cout << "Connected to " << hostname << ":" << port << std::endl;
		isConnected = true;


		socket.receive(packet);
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
