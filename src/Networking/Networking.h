#pragma once
#include <iostream>
#include <string>
#include <winsock2.h>
#include "../Commands/CommandHandler.h"
#include "../Commands/Commands.h"
#include "../Utils/Utils.h"
#include <fstream>
#include <algorithm>
#include "../../external/json/json.hpp"
#include "../../external/lua/lua.h"
#include "../../external/lua/lauxlib.h"
#include "../../external/lua/lualib.h"

class Network
{
    using json = nlohmann::json;
	using base64 = cppcodec::base64_rfc4648;

    public:
        Network(char ip[], int port);
        ~Network();

        void start();

        json recv_(SOCKET clientSocket);
        void send_(SOCKET clientSocket, const json data);
        static std::string compress(const std::vector<char>& data);
        
        struct ClientPacket;
        struct ServerPacket;

    private:
        int port;
        const char* ip;
        
        int bufferSize;
        char* buffer;
};