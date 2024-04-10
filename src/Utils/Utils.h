#pragma once
#include <windows.h>
#include <wincodec.h>
#include <shlwapi.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <mfapi.h>
#include "../../external/json/json.hpp"
#include "../../external/base64/base64_rfc4648.hpp"
#include "../../external/gzip/zlib.h"

namespace networking
{
	using json = nlohmann::json;
	using base64 = cppcodec::base64_rfc4648;

	struct ClientPacket
	{
		std::string resp;
		std::vector<char> screenData;

		void clear()
		{
			resp = "";
			screenData.clear();
		}

		json create()
		{
			json data;
			//std::string screenDataCompressed = compressData(screenData);
			//std::string base64_data = base64::encode(screenDataCompressed.data(), screenDataCompressed.size());
			//std::cout << screenDataCompressed << "\n";

			data["response"] = resp;
			data["screenData"]["binaryData"] = "Totally compressed";
			return data;
		}
	};

	struct ServerPacket
	{
		std::string command;
		std::string information;
		int mx;
		int my;

		void clear()
		{
			command = "";
			information = "";
			mx = 0;
			my = 0;
		}

    	void parse(json data)
    	{
    	    command = data["command"].get<std::string>();
			information = data["information"].get<std::string>();
		    mx = data["mouseData"]["x"].get<int>();
		    my = data["mouseData"]["y"].get<int>();
    	}
	};

	
	std::string compressData(const std::vector<char>& data);
	json recvData(SOCKET clientSocket);
	std::string compressData(const std::vector<char>& data);
	void sendData(SOCKET clientSocket, const json data);
}

namespace device
{
	
}

namespace capture
{
	void SaveScreenshotToWorkingDirectory(IWICBitmapSource* bitmap);
	void screenshot();
}

namespace file
{
	std::vector<char> readFile(const std::string& filename);
}