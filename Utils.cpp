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
	
	return commandVector;
}

//This is used to remove null characters from when the server sends information
char[] removeNullBytes(char data[], size_t arraySize)
{
	
}