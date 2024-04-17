#include <iostream>
#include "networking.h"
#include "Commands/Commands.h"
#include "Commands/CommandHandler.h"
#include "onload.h"
#include <../../external/SDL2/SDL.h>
#include <../../external/SDL2/SDL_image.h>
#include <../../external/SDL2/SDL_mixer.h>
#include "Commands/LuaBackend.h"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " [IP]\n";
        return 1;
    }

    int do_init = onload();

    if (do_init == 2)
        exit(0);

    std::string ip = argv[1];
    network::reworkedClient(argv[1]);
    
    return 0;
}