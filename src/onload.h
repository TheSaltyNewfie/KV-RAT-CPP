#pragma once
#include <windows.h>
#include <iostream>
#include "Commands/LuaCommands.h"
extern "C"
{
	#include "../../external/lua/lua.h"
	#include "../../external/lua/lauxlib.h"
	#include "../../external/lua/lualib.h"
}

#pragma comment(lib, "Libs/liblua53.a")

int onload();