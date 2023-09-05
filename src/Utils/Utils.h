#pragma once
#include <windows.h>
#include <wincodec.h>
#include <shlwapi.h>
#include <iostream>
#include <fstream>
#include <vector>
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "Shlwapi.lib")

namespace capture
{
	void SaveScreenshotToWorkingDirectory(IWICBitmapSource* bitmap);
	void screenshot();
}

namespace file
{
	std::vector<char> readFile(const std::string& filename);
}