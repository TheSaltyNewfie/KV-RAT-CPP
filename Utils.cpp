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
#include <chrono>

namespace serverActions
{
	sf::Packet readyMessage()
	{
		int data = 1;
		sf::Packet datapacket;

		datapacket << data;

		return datapacket;
	}
}

namespace logging
{
	sf::Packet logger(std::string content, bool sendToServer)
	{
		std::string debugMessage = "[DEBUG]: ";

		if(sendToServer)
		{
			sf::Packet debugInfo;
			std::cout << debugMessage << content;
			debugInfo << content;

			return debugInfo;
		}
		else
		{
			std::cout << debugMessage << content;
		}
	}
}

namespace StringUtils
{
	void experimentalSplit(std::string s, std::vector<std::string> &v)
	{
    	std::string temp = "";
    	char quotationcode = '\u0027';
    	char space = ' ';
    	int markcount = 0;
    
    	for(int i = 0; i < s.length(); ++i)
    	{
        	if(s[i] == quotationcode)
        	{
            	++i;
            	++markcount;
            	while(markcount < 2)
            	{
                	if(s[i] == quotationcode)
                	{
                    	v.push_back(temp);
                    	temp = "";
                    	++markcount;
                	}
                	else
                	{
                    	temp.push_back(s[i]);
                    	++i;   
                	}
            	}
            	markcount = 0;
        	}
        
        	if(s[i] == space)
        	{
            	if(temp.size() > 2)
            	{
                	v.push_back(temp);
                	temp = "";
            	}
        	}
        	if(s[i] != quotationcode and s[i] != space)
        	{
            	temp.push_back(s[i]);
        	}
    	}
	}

	void splitString(std::string s, std::vector<std::string> &v) //Keeping for legacy reasons
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
}

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

	if (commands[0] == "playAudio")
	{
		std::cout << "Not available";
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

sf::Packet timeoutReset() // Just sends a message to the server letting it know the connection is still open
{
	std::string upkeepmsg = "timeoutReset";
	sf::Packet datatosend;

	datatosend << upkeepmsg;

	return datatosend;
}

sf::Packet logger(std::string content, bool sendToServer)
{
	std::string debugMessage = "[DEBUG]: ";

	if(sendToServer)
	{
		sf::Packet debugInfo;
		std::cout << debugMessage << content;
		debugInfo << content;

		return debugInfo;
	}
	else
	{
		std::cout << debugMessage << content;
	}
}

void processPacket(sf::TcpSocket socket, sf::Packet packet, std::string data)
{
	socket.receive(packet);
	packet >> data;
}



int getAproxPing(sf::Packet packet)
{
	std::string serversTime;
	//std::string clientTime;

	const auto p1 = std::chrono::system_clock::now();
	auto clientTime = std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count();

	//logger(clientTime, false);
}
