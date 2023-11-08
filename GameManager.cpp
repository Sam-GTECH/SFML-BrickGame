#include "GameManager.h"
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

GameManager::GameManager(int limit, bool vsync)
{
	window.create(sf::VideoMode(640, 480), "SFML", sf::Style::Close);
	window.setFramerateLimit(limit);
	window.setVerticalSyncEnabled(vsync);

	sf::Font font;
	show_fps = font.loadFromFile("arial.ttf");

	sf::Text text;
	if (show_fps)
	{
		text.setFont(font);
		text.setString("FPS: 0");
		text.setCharacterSize(16);
		text.setFillColor(sf::Color::White);
	}

	//Input.game = this;

	GameObject* obj = new GameObject(100.f, 100.f, sf::Color::Blue, 50.f, 50.f);
	GameObject* obj2 = new GameObject(320, 240.f, sf::Color::Green, 50.f);
	objects.push_back(obj);
	objects.push_back(obj2);

	Input.addInputEvent(sf::Event::MouseButtonPressed, []() -> bool {cout << "olee chitte" << endl; return true; });
	Input.addInputEvent(sf::Event::MouseButtonPressed, []() -> bool {cout << "olee chitte 2.0" << endl; return false; });
}

GameManager::~GameManager()
{
	window.~RenderWindow();
	for (int i = 0; i < objects.size(); i++)
	{
		delete objects[i];
	}
}

void GameManager::gameLoop()
{
	while (run && window.isOpen())
	{
		sf::Event oEvent;
		while (window.pollEvent(oEvent))
		{
			if (oEvent.type == sf::Event::Closed)
			{
				window.close();
				run = false;
				break;
			}
			Input.handleEvents(oEvent);
		}

		// If an event stopped the game, break from the game loop
		if (!run)
			break;

		update();

		window.clear();

		draw();

		deltaTime = deltaClock.restart().asSeconds();
	}
}

void GameManager::update()
{
	sf::Vector2i m = Input.getMousePos();
	cout << m.x << " - " << m.y << endl;
	sf::Vector2i p = window.getPosition();
	cout << p.x << " - " << p.y << endl;
	if (show_fps)
	{
		fpsTimer += deltaTime;
		fpsCount += 1.f;
		if (fpsTimer >= 1.f)
		{
			FPS = static_cast<float>(fpsCount) / fpsTimer;
			fpsCount = 0;
			fpsTimer -= 1.f;

			snprintf(fpsText, sizeof(fpsText), "FPS: %i", FPS);
			text.setString(fpsText);
		}
	}
	cout << "--------------------" << endl;
}

void GameManager::draw()
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->draw(window);
	}

	window.draw(text);

	window.display();
}