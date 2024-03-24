#pragma once
//#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string>
#include <winsock2.h>
#include "Commands/CommandHandler.h"
#include "Commands/Commands.h"
#include "Utils/Utils.h"
#include <fstream>
#include <algorithm>
#include "../../external/json/json.hpp"

extern "C"
{
	#include "../../external/lua/lua.h"
	#include "../../external/lua/lauxlib.h"
	#include "../../external/lua/lualib.h"
}


//#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "../../Libs/liblua53.a")

namespace network
{
	void client(char ip[]);
	int reworkedClient(char ip[]);
}