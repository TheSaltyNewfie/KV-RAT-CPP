#include <iostream>
#include <Windows.h>
#include <vector>
#include <SFML/Audio.hpp>
#include "Utils.h"

/*
Takes 3 inputs, file path, delay, delay amount

This uses SFML for streaming and playing the audio and is considered music so it will be streamed
returns 1 if it errors out, returns 0 if it was successful.
*/
int playAudio(std::string& fpath, bool delay = false, float delayTime = 0)
{
    if(delay)
    {
        sleep(delayTime);
    }

    sf::Music audio;
    if(!audio.openFromFile(fpath))
    {
        return 1;
    }
    audio.play();
    return 0;
}

void showUpdateWindow(std::string& header, std::string& text)
{
    
}