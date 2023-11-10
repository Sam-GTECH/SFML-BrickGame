#include "GameManager.h"
#include "GameObject.h"
#include "Canon.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

GameManager::GameManager(int limit, bool vsync)
{
	window.create(sf::VideoMode(640, 480), "SFML", sf::Style::Close);
	window.setFramerateLimit(limit);
	window.setVerticalSyncEnabled(vsync);

	show_fps = font.loadFromFile("arial.ttf");

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
	Canon* caac = new Canon(640 / 2, 440, sf::Color::Cyan, 100.f, 50.f);
	addChild(obj);
	addChild(obj2);
	addChild(caac);

	Input.addInputEvent(sf::Event::MouseButtonPressed, [](sf::Event::EventType event) -> bool {
		cout << "olee chitte" << endl;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			cout << "el rightto" << endl;
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cout << "el leftto" << endl;
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
			cout << "ur mid" << endl;
		/*else if (event.mouseButton.button == sf::Mouse::XButton1)
			cout << "Gamer Mouse 1" << endl;
		else if (event.mouseButton.button == sf::Mouse::XButton2)
			cout << "Gamer Mouse 2" << endl;*/
		return true;
	});
	Input.addInputEvent(sf::Event::MouseButtonPressed, [](sf::Event::EventType event) -> bool {cout << "olee chitte 2.0" << endl; return false; });
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
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->update(deltaTime);
	}

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

void GameManager::addChild(GameObject* obj)
{
	objects.push_back(obj);
	obj->Input = &Input;
	obj->Game = this;
	obj->postInit();
}