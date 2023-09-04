#pragma once
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

namespace commands
{
	void showMessageBox(const std::vector<std::string>& args);
	void execute(const std::vector<std::string>& args);
	void cringe();
}