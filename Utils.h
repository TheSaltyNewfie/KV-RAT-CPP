#pragma once
#include <Windows.h>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <vector>
#include <sstream>

void message(sf::TcpSocket& server, std::string& msg);

std::string byteToString(char bytes[], size_t actualsize);

std::vector<std::string> returnCommands(char data[50], size_t arraySize);
