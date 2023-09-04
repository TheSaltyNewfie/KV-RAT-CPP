#include <iostream>
#define ASIO_STANDALONE
#include "networking.h"
#include "Commands/Commands.h"
#include "Commands/CommandHandler.h"
#include "onload.h"
#include <thread>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " [server|client] [IP]\n";
        return 1;
    }

    int do_init = onload();

    if (do_init == 2)
        exit(0);

    std::string mode = argv[1];
    if (mode == "client")
    {
        network::client(argv[2]);
    }
    else if (mode == "server")
    {
        network::server();
    }
    else if (mode == "SDL_Test")
    {
        commands::cringe();
    }
    else
    {
        std::cerr << "Invalid mode. Check usage\n";
        return 1;
    }

    return 0;
}