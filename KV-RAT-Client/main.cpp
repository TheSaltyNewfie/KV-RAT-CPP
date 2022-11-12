#include <iostream>
#include <SFML/Network.hpp>
#include "Utils.h"
#include "ScreenCapture.h"
#include <thread>

struct {
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
		HBITMAP lbitmap = GetScreenShot();
		std::cout << "HBITMAP DATA: " << ((char*)(lbitmap), sizeof(lbitmap)) << "||" << lbitmap << "\n";
		
		//lpacket << ((BYTE*)(lbitmap), sizeof(lbitmap));
		//lpacket << lbitmap;

		socket.send(lbitmap, sizeof(lbitmap));

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

	return 0;
}