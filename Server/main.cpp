#include <iostream>
#include <SFML/Network.hpp>
#include <vector>

void packet_cleaner(std::vector<sf::Packet> &packets)
{
	for (int i = 0; i < packets.size(); ++i)
	{
		packets[i].clear();
		i++;
	}
	std::cout << "packets cleaned!";
}

int main()
{
	std::string user_input;
	sf::Packet packet;
	sf::TcpListener listener;
	sf::Packet client_data;
	std::string client_data_format;
	bool client_connected = false;

	while (true)
	{
		if (listener.listen(4560) != sf::Socket::Done)
		{
			std::cout << "Something errored but I am too lazy to write a proper error thing so fuck you future me\n";
		}
		sf::TcpSocket client;
		if (listener.accept(client) != sf::Socket::Done)
		{
			std::cout << "Fuck you, you get nothing\n";
		}

		client_connected = true;

		while (client_connected)
		{


			/*
			std::getline(std::cin, user_input);
			std::cout << "This is what is containt in the balls: " << user_input << "\n";
			packet << user_input;
			client.send(packet);
			packet.clear();
			user_input.clear();
			*/
		}
	}

	return 0;
}

