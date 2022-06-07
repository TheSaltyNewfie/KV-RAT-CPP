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

void ParseCommand(std::vector<std::string> commands)
{
	if (commands[0] == "showMessageWindow")
	{
		showMessageWindow(commands[1], commands[2], 800, 600);
	}
}

DWORDLONG allocated_memory()
{
	PROCESS_MEMORY_COUNTERS_EX pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
	SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
	DWORDLONG physMemUsed = pmc.WorkingSetSize;

	return physMemUsed;
}

sf::Packet logger(std::string &content, bool sendToServer = false;)
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

std::vector<std::string> dataParser(std::string[] data)
{
	std::string dataParsed;
	/*TODO: parse the data as such
		Example: {"entryOne": "entryOneInfo"}

	*/
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