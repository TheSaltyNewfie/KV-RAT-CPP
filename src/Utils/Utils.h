#pragma once
#include <windows.h>
#include <wincodec.h>
#include <shlwapi.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <mfapi.h>
#include "../../external/json/json.hpp"
//#pragma comment(lib, "windowscodecs.lib")
//#pragma comment(lib, "Shlwapi.lib")

namespace networking
{
	using json = nlohmann::json;

	json recvData(SOCKET clientSocket);
	std::string recvDataSTR(SOCKET clientSocket);
	void sendData(SOCKET clientSocket, const json data);
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