#pragma once
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

void message(sf::TcpSocket& server, std::string& msg);

std::string byteToString(char bytes[], size_t actualsize);

void splitString(std::string s, std::vector<std::string>& v);

void ParseCommand(std::vector<std::string> commands);
