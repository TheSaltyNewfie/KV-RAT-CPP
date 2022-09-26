#define NOMINMAX
#include <Windows.h>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
//#include <gdiplus.h>
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

	void local(std::string content)
	{
		std::cout << "[LOG] " << content << std::endl;
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

			std::cout << "WORD: " << temp << "\n";
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

void ParseCommand(std::vector<std::string> commands)
{
	if (commands[0] == "showMessageWindow")
	{
		showMessageWindow(commands[1], commands[2], 800, 600);
	}

	if (commands[0] == "execute")
	{
		std::cout << "We are executing some stuff\n";
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
BITMAPINFOHEADER createBitmapHeader(int width, int height)
{
	BITMAPINFOHEADER  bi;

	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = width;
	bi.biHeight = -height;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	return bi;
}

HBITMAP GdiPlusScreenCapture(HWND hWnd)
{
	HDC hwindowDC = GetDC(hWnd);
	HDC hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
	SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);

	int scale = 1;
	int screenx = GetSystemMetrics(SM_XVIRTUALSCREEN);
	int screeny = GetSystemMetrics(SM_YVIRTUALSCREEN);
	int width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	int height = GetSystemMetrics(SM_CYVIRTUALSCREEN);

	HBITMAP hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
	BITMAPINFOHEADER bi = createBitmapHeader(width, height);

	SelectObject(hwindowCompatibleDC, hbwindow);

	DWORD dwBmpSize = ((width * bi.biBitCount + 31) / 32) * 4 * height;
	HANDLE hDIB = GlobalAlloc(GHND, dwBmpSize);
	char* lpbitmap = (char*)GlobalLock(hDIB);

	StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, screenx, screeny, width, height, SRCCOPY);
	GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, lpbitmap, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

	DeleteDC(hwindowCompatibleDC);
	ReleaseDC(hWnd, hwindowDC);

	return hbwindow;
}

sf::Packet sendScreenCapture(HBITMAP bitmap)
{
	sf::Packet bitmapStuff;

	bitmapStuff << bitmap;

	return bitmapStuff;
}
*/


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
