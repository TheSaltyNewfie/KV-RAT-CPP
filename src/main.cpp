#include <iostream>
#include "Networking/Networking.h"
#include "Commands/Commands.h"
#include "Commands/CommandHandler.h"
#include <../../external/SDL2/SDL.h>
#include <../../external/SDL2/SDL_image.h>
#include <../../external/SDL2/SDL_mixer.h>
#include "Commands/LuaBackend.h"
#include <cstring>
#include <thread>
#include "Utils/Debug.h"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " [IP]\n";
        return 1;
    }

    int result = MessageBoxW(nullptr, L"KV-RAT has started, but nothing has initalized.\nContinue?", L"KV-RAT", MB_OKCANCEL | MB_ICONEXCLAMATION);
    if (result == 2)
    {
        return 0;
    }

    if(strcmp(argv[1], "-debug") == 0)
    {
        Debug dbg;
        dbg.init();
    }
    /*

    if(strcmp(argv[1], "-l") == 0)
    {
        LuaBackend lb("script.lua");
    }
    else
    {    
        Network client(argv[1], 3002);

        std::thread LuaThread([&]() {
            LuaBackend lb("script.lua");
        });

        std::thread ClientThread([&]() {
            client.start();
        });

        std::thread DataStream([&]() {
            client.tcp_datastream();
        });

        LuaThread.join();
        ClientThread.join();
        DataStream.join();   
    }
    */
    
    return 0;
}