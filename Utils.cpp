#define NOMINMAX
#include <Windows.h>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <sstream>
#include "Utils.h"
#include "Commands.h"

void ParseCommand(std::vector<std::string> commands)
{
	if (commands[0] == "showMessageWindow")
	{
		showMessageWindow(commands[1], commands[2], 800, 600);
	}
}

/*
// Say something on the server side is going to change such as an address or port, the client can know before hand
void changeSettings(sf::TcpSocket& server, std::string& hostname, std::string& port, std::string& debug)
{
	//This part of the code is what changes settings
	std::vector<std::string> data = {hostname, port, debug};

	//changeSettings(data);

	//This part of the code is executed after the settings are changed
	sf::RenderWindow window(sf::VideoMode(256, 512), "Alert");
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
		std::cout << "Error when loading font";	
	sf::Text text("A client setting has changed. Please restart PC or program when possible. Oh and if you see this please tell me kasean, incase something has gone wrong", font, 50);
}
*/

void message(sf::TcpSocket& server, std::string& msg)
{
	//Send a message to the server
}

std::string byteToString(char bytes[], size_t actualsize)
{
	std::string s(bytes, sizeof(actualsize));
	return s;
}

void splitString(std::string s, std::vector<std::string> &v)
{
	std::string temp = "";
	//std::vector<std::string> v;
	for (int i = 0; i < s.length(); ++i)
	{
		if (s[i] == ' ')
		{
			v.push_back(temp);
			temp = "";
		}
		else
		{
			temp.push_back(s[i]);
		}
	}
	v.push_back(temp);

}

/*
std::vector<std::string> returnCommands(char data[50], size_t arraySize)
{
	std::string s;
	std::vector<std::string> commandVector;
	const char delim = ' ';

	std::stringstream ss(s);
	while (std::getline(ss, s, delim))
	{
		commandVector.push_back(s);
	}
	
	return commandVector;
}
*/