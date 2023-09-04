#include <Windows.h>
#include <iostream>
#include <d3d11.h>
#include <tchar.h>

int onload()
{
	std::string message = "KV-RAT has loaded successfully. But if you wish to close it press CANCEL. Otherwise press OK.";
	std::string title = "KV-RAT Loader";

	std::wstring wTitle(title.begin(), title.end());
	std::wstring wMessage(message.begin(), message.end());

	int result = MessageBoxW(nullptr, wMessage.c_str(), wTitle.c_str(), MB_OKCANCEL | MB_ICONEXCLAMATION);

	return result;
}