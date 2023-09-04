#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <sstream>
#include "commands.h"
#include <regex>
#include <iomanip>
#include "../Utils/utils.h"

namespace CommandHandler {
	std::vector<std::string> cleanFunctions(const std::string& input);
	void callFunction(const std::vector<std::string>& input);
}