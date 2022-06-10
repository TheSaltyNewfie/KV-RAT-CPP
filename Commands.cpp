#include <iostream>
#define NOMINMAX
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <SFML/Audio.hpp>
#include "Utils.h"

/*
Takes 3 inputs, file path, delay, delay amount

This uses SFML for streaming and playing the audio and is considered music so it will be streamed
returns 1 if it errors out, returns 0 if it was successful.
*/
int playAudio(std::string& fpath)
{
    sf::Music audio;
    if(!audio.openFromFile(fpath))
    {
        return 1;
    }
    audio.play();
    return 0;
    logger("Music was played", false);
}

void execute(std::string url)
{
    std::wstring stemp = std::wstring(url.begin(), url.end());
    LPCWSTR sw = stemp.c_str();

    ShellExecute(0, 0, sw, 0, 0, SW_SHOW);
}

void lookatye()
{
    sf::RenderWindow window(sf::VideoMode(680, 680), "Look at ye. Postin' cringe");
    sf::Texture texture;
    texture.loadFromFile("179.png");

    sf::Sprite sprite(texture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }
}

void showMessageWindow(std::string& header, std::string& stext, int height, int width)
{
    sf::RenderWindow window(sf::VideoMode(200, 200), header);
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Error loading font...";
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        sf::Text text;
        text.setFont(font);
        text.setString(stext);
        text.setCharacterSize(24);
        window.draw(text);
        window.display();
    }

    /*
    sf::RenderWindow window(sf::VideoMode(1024,1024), header);
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Error loading font...";
    }
    sf::Text text(stext, font, 50);
    */
}
