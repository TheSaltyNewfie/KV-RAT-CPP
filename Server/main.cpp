#include <iostream>
#include <SFML/Network.hpp>
#include <vector>

void packet_cleaner(std::vector<sf::Packet> &packets)
{
	for (int i; i = 0; i < packets.size())
	{
		packets[i].clear();
		i++;
	}
	std::cout << "packets cleaned!";
}

int main()
{
	std::string userinput;
	sf::Packet packet;
	sf::TcpListener listener;
	sf::Packet client_data;
	std::string client_data_format;

	if (listener.listen(4560) != sf::Socket::Done)
	{
		std::cout << "Something errored but I am too lazy to write a proper error thing so fuck you future me\n";
	}
	sf::TcpSocket client;
	if (listener.accept(client) != sf::Socket::Done)
	{
		std::cout << "Fuck you, you get nothing\n";
	}

	while (true)
	{
		//std::cin::getline >> userinput;
		std::getline(std::cin, userinput);
		std::cout << "This is what is containt in the balls: " << userinput << "\n";
		packet << userinput;
		client.send(packet);
		//client.receive(client_data);
		//client_data >> client_data_format;
		//std::cout << "\nClient Data: " << client_data_format << "\n";
		packet.clear();
		userinput.clear();
		//client_data.clear();
	}
	
	return 0;
}

