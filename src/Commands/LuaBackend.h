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
#include <ctime>

extern "C"
{
	#include "../../external/lua/lua.h"
	#include "../../external/lua/lauxlib.h"
	#include "../../external/lua/lualib.h"
}

class LuaBackend
{
    public:
        LuaBackend(std::string Script);
        ~LuaBackend();

        static int SDLWindow(lua_State* L); // Returns void
        static int moveMouse(lua_State* L); // Returns void
        
        static int getMouseX(lua_State* L); // Returns int
        static int getMouseY(lua_State* L); // Returns int
        static int setMouseX(lua_State* L); // Returns void
        static int setMouseY(lua_State* L); // Returns void

        static int getScreenWidth(lua_State* L); // Returns int
        static int getScreenHeight(lua_State* L); // Returns int

        static int getTime(lua_State* L); // Returns string
        static int getDay(lua_State* L); // Returns string
    private:
        lua_State* L;
};