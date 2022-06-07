#pragma once
#define NOMINMAX
#include <Windows.h>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <sstream>
#include <TCHAR.h>
#include <pdh.h>
#include "Utils.h"
#include "Commands.h"

void doCommandStuff(std::string data, std::vector<std::string> otherData, bool breuh);

sf::Packet logger(std::string &content, bool sendToServer = false;);

DWORDLONG allocated_memory();

void processPacket(sf::TcpSocket socket, sf::Packet packet, std::string data);

std::string byteToString(char bytes[], size_t actualsize);

void splitString(std::string s, std::vector<std::string>& v);

void ParseCommand(std::vector<std::string> commands);
