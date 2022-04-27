#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include <SFML/Audio.hpp>
#include "Utils.h"

int playAudio(std::string& fpath, bool delay = false, float delayTime = 0);