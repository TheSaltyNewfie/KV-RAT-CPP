#pragma once
#include <Windows.h>
#include <wincodec.h>
#include <Shlwapi.h>
#include <iostream>
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "Shlwapi.lib")

namespace capture
{
	void SaveScreenshotToWorkingDirectory(IWICBitmapSource* bitmap);
	void screenshot();
}