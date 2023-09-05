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
    /*
        For now we will just do the basic if clauses. Too lazy to figure out function calling from string rn
    */

    std::cout << "DEBUG: " << input[0] << "SPACE\n";
    if (input[0] == "Message ")
    {
        commands::showMessageBox({ input[1], input[2] });
        printf("Called showMessageBox('% s', '% s')\n", input[1], input[2]);
    }

    if (input[0] == "Execute ")
    {
        commands::execute({input[1]});
    }

    if (input[0] == "Cringe ")
    {
        commands::cringe();
    }

    if (input[0] == "screentest ")
    {
        capture::screenshot();
    }

    if(input[0] == "kys ")
    {
        commands::KillYourSelf();
    }
}