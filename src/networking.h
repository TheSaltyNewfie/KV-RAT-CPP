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


//#pragma comment(lib, "ws2_32.lib")

namespace network
{
	void client(char ip[]);

	void server();
}