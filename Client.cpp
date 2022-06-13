#include <iostream>
#include <SFML/Network.hpp>
#include "Utils.h"
#include <thread>

extern "C"
{
#include "Lua542/include/lua.h"
#include "Lua542/include/lauxlib.h"
#include "Lua542/include/lualib.h"
}

#ifdef _WIN32
#pragma comment(lib, "lua542/liblua54.a")
#endif

struct{
	std::string hostname = "71.7.242.3";
	int port = 4560;
} config;

struct{
	int code; // 100 means OK, 200 means Error, 300 means disconnecting
	std::string name; // This only represents the name of the server we connect to.
} serverInfo;

int main()
{
		sf::Packet packet;
		std::string data;
		std::vector<std::string> v;

		sf::Packet statusData;

		bool isConnected = false;

	while(true)
	{
		sf::TcpSocket socket;
		sf::Socket::Status status = socket.connect(config.hostname, config.port);

		if(status != sf::Socket::Done)
		{
			std::cout << "Unable to connect to server " << hostname << ":" << port;
		}
		std::cout << "Connected to " << hostname << ":" << port << std::endl;
		isConnected = true;

		while(isConnected)
		{
			socket.send(serverActions::readyMessage());
			socket.receive(statusData);
			statusData >> serverInfo.code;
			if(serverInfo.code == "100")
			{
				socket.receive(packet);
				packet >> data;
				StringUtils::experimentalSplit(data, v);
				ParseCommand(v);
			}
			if(serverInfo.code == "200")
			{
				std::cout << "Error occurred on the server side..." << std::endl;
			}
			if(serverInfo.code == "300")
			{
				std::cout << "Server is closing..." << std::endl;
				socket.disconnect();
				isConnected = false;
			}
		}
	}
	


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
