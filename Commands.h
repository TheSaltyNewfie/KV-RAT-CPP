#pragma once
#include <iostream>
#define NOMINMAX
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <SFML/Audio.hpp>
#include "Utils.h"


int playAudio(std::string& fpath);
void showMessageWindow(std::string& header, std::string& stext, int height, int width);
void startVideo(std::string url);