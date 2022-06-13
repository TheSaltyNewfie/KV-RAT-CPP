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

sf::Packet timeoutReset();

sf::Packet logger(std::string content, bool sendToServer);

void processPacket(sf::TcpSocket socket, sf::Packet packet, std::string data);

std::string byteToString(char bytes[], size_t actualsize);

void experimentalSplit(std::string s, std::vector<std::string>& v);

void splitString(std::string s, std::vector<std::string>& v);

void ParseCommand(std::vector<std::string> commands);
