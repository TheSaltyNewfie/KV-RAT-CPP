#pragma once
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <vector>
#include <../../external/SDL2/SDL.h>
#include <../../external/SDL2/SDL_image.h>
#include <../../external/SDL2/SDL_mixer.h>

namespace commands
{
	void showMessageBox(const std::vector<std::string>& args);
	void execute(const std::vector<std::string>& args);
	void cringe();
	void KillYourSelf();
}