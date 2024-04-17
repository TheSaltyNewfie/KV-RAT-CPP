#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <sstream>
#include "Commands.h"
#include <regex>
#include <iomanip>
#include <thread>
#include "../Utils/Utils.h"

class CommandHandler 
{
	public:
		std::string rawInput;
		std::vector<std::string> args;
		bool Debug = false;

		CommandHandler();
		~CommandHandler();
		void clean();
		void callFunction();
		void setInput(std::string input);

	private:
		void DebugPrint();
};