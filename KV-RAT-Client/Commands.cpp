#include <iostream>
#define NOMINMAX
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <SFML/Audio.hpp>
#include "Utils.h"


int playAudio(std::string& fpath)
{
    sf::Music audio;
    if (!audio.openFromFile(fpath))
    {
        return 1;
    }
    audio.play();
    return 0;
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
}

void moveMouse(int x, int y)
{
    int x2 = 0;
    int y2 = 0;
    bool shouldrun = true;

    while (shouldrun)
    {
        if (x > x2)
        {
            x2 += 1;
        }
        else
        {
            if (y > y2)
            {
                y2 += 1;
            }
            else
            {
                shouldrun = false;
            }
        }
        //cout << "X Y = " << x << " " << y << endl << "X2 Y2 = " << x2 << " " << y2 << endl;
        SetCursorPos(x2, y2);
    }
}

/*
void hampter()
{
    try
    {
        sf::RenderWindow hamptime(sf::VideoMode(1920, 1080), "HAMPTER TIME :)", sf::Style::Fullscreen);
        sf::Texture texture;
        texture.loadFromFile("img/hampter.jpg");
        sf::Sprite sprite(texture);
        sf::Music audio;
        if (!audio.openFromFile("audio/hampterd.mp3"))
        {
            std::cout << "Yo we dead!";
        }
        while (hamptime.isOpen())
        {
            sf::Event event;
            while (hamptime.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    hamptime.close();
            }
            audio.play();
            hamptime.clear();
            hamptime.draw(sprite);
            hamptime.display();
        }
    }
    catch (const std::exception& e) { std::cout << e.what(); }
}
*/