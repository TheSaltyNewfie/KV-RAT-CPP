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

	bool isConnected = false;

	while (true)
	{
		if (status != sf::Socket::Done)
			std::cout << "Unable to connect to server " << hostname << ":" << port;
		std::cout << "Connected to " << hostname << ":" << port << std::endl;
		isConnected = true;

		if (status == sf::Socket::Disconnected)
		{
			//break;
		}

		while(!isConnected) // This absolutely doesnt work, I can already tell
		{
			std::cout << "Disconnected from server, retrying in 5 seconds" << std::endl;
			sleep(5000);
			socket.connect(hostname, port);
		}


		socket.receive(packet);
		packet >> data;

		std::cout << "Data:" << data << std::endl << "Received:" << "Maybe 3 could be 4" << std::endl;
		//experimentalSplit(data, v);
		experimentalSplit(data, v);
		processingCommand = true;
		ParseCommand(v);
		std::cout << "VECTOR DATA: " << v.size();
		v.clear();
		data.clear();
		packet.clear();
	}
	
	return 0;
}
