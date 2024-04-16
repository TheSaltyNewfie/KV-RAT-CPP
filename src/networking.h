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
#include "../../external/lua/lua.h"
#include "../../external/lua/lauxlib.h"
#include "../../external/lua/lualib.h"

namespace network
{
	int reworkedClient(char ip[]);
}