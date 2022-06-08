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
	splitString(data, otherdata);
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

	if (commands[0] == "startVideo")
	{
		startVideo(commands[1]);
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
		return NULL;
	}
	return NULL;
}

void processPacket(sf::TcpSocket socket, sf::Packet packet, std::string data)
{
	socket.receive(packet);
	packet >> data;
}

void YOOOexperimentalsplit(std::string s, std::vector<std::string> &v)
{
    std::string temp = "";
    char quotationcode = '\u0027';
    char space = ' ';
    int markcount = 0;
    
    for(int i = 0; i < s.length(); ++i)
    {
        //std::cout << "Temp at cycle: " << i << " = " << temp << std::endl;
        
        if(s[i] == quotationcode)
        {
            ++i;
            ++markcount;
            while(markcount < 2)
            {
                if(s[i] == quotationcode)
                {
                    //std::cout << "quotationcode found in slot: " << i << " " << s[i] << "markcount: " << markcount << std::endl;
                    //std::cout << temp << std::endl;
                    v.push_back(temp);
                    temp = "";
                    ++markcount;
                    //std::cout << "breaking while loop" << std::endl;
                }
                else
                {
                    //std::cout << "word arg found in slot: " << i << " " << s[i] << std::endl;
                    temp.push_back(s[i]);
                    ++i;   
                }
            }
            markcount = 0;
        }
        
        if(s[i] == space)
        {
            //std::cout << "space found in slot: " << i << " " << s[i] << std::endl;
            if(temp.size() > 2)
            {
                v.push_back(temp);
                temp = "";
            }
        }
        if(s[i] != quotationcode and s[i] != space)
        {
            //std::cout << "word found in slot: " << i << " " << s[i] << std::endl;
            temp.push_back(s[i]);
        }
        //std::cout << "-------" << std::endl;
    }
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