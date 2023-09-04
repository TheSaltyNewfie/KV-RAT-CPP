#pragma once
#include <windows.h>
#include <wincodec.h>
#include <shlwapi.h>
#include <iostream>
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "Shlwapi.lib")

namespace capture
{
	void SaveScreenshotToWorkingDirectory(IWICBitmapSource* bitmap);
	void screenshot();
}