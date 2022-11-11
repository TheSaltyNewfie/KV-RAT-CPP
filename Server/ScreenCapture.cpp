#include <SFML/Graphics.hpp>
#define NOMINMAX
#include <objidl.h>
#include <gdiplus.h>
#include <gdiplustypes.h>
#include<iostream>
#include <windows.h>
#pragma comment (lib,"Gdiplus.lib")


void displayScreenCapture(HBITMAP hbitmap)
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Screen Cap");

	sf::Texture screenshot;
	sf::Sprite sprite;

	if (!screenshot.loadFromMemory(hbitmap, sizeof(hbitmap)))
	{
		std::cout << "Error when loading from memory";
	}

	sprite.setTexture(screenshot);
	sprite.setScale(1280, 720);

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