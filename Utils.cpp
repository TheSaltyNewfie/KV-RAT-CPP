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

void doCommandStuff(std::string data, std::vector<std::string> otherData, bool breuh)
{
	splitString(data, otherData);
	breuh = true;
	ParseCommand(otherData);
	breuh = false;
}

void ParseCommand(std::vector<std::string> commands)
{
	if (commands[0] == "showMessageWindow")
	{
		showMessageWindow(commands[1], commands[2], 800, 600);
	}

	if (commands[0] == "execute")
	{
		execute(commands[1]);
	}

	if (commands[0] == "lookatye")
	{
		lookatye();
	}
}

/*
DWORDLONG allocated_memory()
{
	PROCESS_MEMORY_COUNTERS_EX pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
	SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
	DWORDLONG physMemUsed = pmc.WorkingSetSize;

	return physMemUsed;
}
*/

sf::Packet logger(std::string &content, bool sendToServer)
{
	if(sendToServer)
	{
		sf::Packet debugInfo;
		std::cout << content;
		debugInfo << content;

		return debugInfo;
	}
	else
	{
		std::cout << content;
	}
}

void processPacket(sf::TcpSocket socket, sf::Packet packet, std::string data)
{
	socket.receive(packet);
	packet >> data;
}

void experimentalSplit(std::string s, std::vector<std::string>& v)
{
	int marks = 0;

	std::string temp = "";
	for (int i = 0; i < s.length(); ++i)
	{
		if (s[i] == '"')
		{
			std::cout << "found first quotation" << std::endl;
			if (s[i] != '"')
			{
				std::cout << "letter in quotes: " << s[i] << std::endl;
				temp.push_back(s[i]);
				++i;
			}
			else
			{
				std::cout << "found second quotation" << std::endl;
				v.push_back(temp);
				temp = "";
			}
		}
		else if (s[i] == ' ')
		{
			v.push_back(temp);
			temp = "";
		}
		else
		{
			temp.push_back(s[i]);
		}
		v.push_back(temp);
	}

}

void splitString(std::string s, std::vector<std::string> &v)
{
	std::string temp = "";
	//std::vector<std::string> v;
	for (int i = 0; i < s.length(); ++i)
	{
		if (s[i] == ';')
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