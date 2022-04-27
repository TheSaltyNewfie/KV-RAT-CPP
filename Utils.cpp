#include <Windows.h>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <vector>
#include <sstream>
#include "Utils.h"

void message(sf::TcpSocket& server, std::string& msg)
{
	//Send a message to the server
}

std::string byteToString(char bytes[], size_t actualsize)
{
	std::string s(bytes, sizeof(actualsize));
	return s;
}

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

	/*
	int i;
	int size = static_cast<int>(arraySize);
	std::string s = "";
	std::vector<std::string> commandVector;

	for (i = 0; i < size; i++) 
	{
		s = s + data[i];
	}
	*/
	

	return commandVector;
}