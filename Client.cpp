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
	std::string hostname = "192.168.2.85";
	int port = 4560;
} config;

int main()
{
	sf::Packet packet;
	std::string data;
	std::vector<std::string> v;

	sf::Packet statusData;

	bool isConnected = false;
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
			isConnected = true;

			while (isConnected)
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
	catch (std::exception& e) { std::cout << e.what(); }
	
	/*
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
