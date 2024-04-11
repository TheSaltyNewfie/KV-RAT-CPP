#pragma once
#include <iostream>
#include <stdio.h>
#include <string>
#include <windows.h>
#include <vector>
#include <mfapi.h>
#define SDL_MAIN_HANDLED
#include <../../external/SDL2/SDL.h>
#include <../../external/SDL2/SDL_image.h>
#include <../../external/SDL2/SDL_mixer.h>
#include "../Utils/Utils.h"

namespace commands
{
	void showMessageBox(const std::vector<std::string>& args);
	void execute(const std::string& argument);
	void cringe();
	void feesh();
	void KillYourSelf();
	void StopProcess();
	std::vector<char> Screenshot_C();
	void randomPixel(int x, int y, int radius);
}