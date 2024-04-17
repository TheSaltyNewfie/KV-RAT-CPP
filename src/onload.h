#pragma once
#include <windows.h>
#include <iostream>
#include "Commands/LuaBackend.h"
extern "C"
{
	#include "../../external/lua/lua.h"
	#include "../../external/lua/lauxlib.h"
	#include "../../external/lua/lualib.h"
}

int onload();