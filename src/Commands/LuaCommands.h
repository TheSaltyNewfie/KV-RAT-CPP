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
#include <../../external/SDL2/SDL_ttf.h>
#include "../Utils/Utils.h"
extern "C"
{
	#include "../../external/lua/lua.h"
	#include "../../external/lua/lauxlib.h"
	#include "../../external/lua/lualib.h"
}

int SDLWindow(lua_State *L);

int moveMouse(lua_State *L);
