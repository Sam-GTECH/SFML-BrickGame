#include "GameManager.h"
#include "GameObject.h"
#include "Canon.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

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

	Input.game = this;

	GameObject* obj = new GameObject(100.f, 100.f, sf::Color::Blue, 50.f, 50.f);
	GameObject* obj2 = new GameObject(320, 240.f, sf::Color::Green, 50.f);
	Canon* caac = new Canon(640 / 2, 440, sf::Color::Cyan, 100.f, 50.f);
	addChild(obj);
	addChild(obj2);
	addChild(caac);
// 	obj->setVector(1, 1);
// 	GameObject* brick1 = new GameObject(320.f, 100.f, sf::Color::Green, 50.f, 50.f);
// 	GameObject* brick2 = new GameObject(420.f, 100.f, sf::Color::Green, 50.f, 50.f);
// 	GameObject* brick3 = new GameObject(520.f, 100.f, sf::Color::Green, 50.f, 50.f);
	//GameObject* obj2 = new GameObject(320, 240.f, sf::Color::Green, 50.f);
// 	bullets.push_back(obj);
// 	blocks.push_back(brick1);
// 	blocks.push_back(brick2);
	//blocks.push_back(brick3);

	Input.addInputEvent(this, sf::Event::MouseButtonPressed, [](GameManager* game, sf::Event::EventType event) -> bool {
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
	Input.addInputEvent(this, sf::Event::LostFocus, [](GameManager* game, sf::Event::EventType event) -> bool {cout << "olee chitte 2.0" << endl; return false; });
}

GameManager::~GameManager()
{
	window.~RenderWindow();
	for (int i = 0; i < blocks.size(); i++)
	{
		delete blocks[i];
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
	for (int i = 0; i < objects.size(); i++)
	{
		delete objects[i];
	}
}

bool GameManager::rectOverlap(GameObject& object1, GameObject& object2)
{
	return object1.x < object2.x + object2.width && object1.x + object1.width > object2.x && object1.y < object2.y + object2.height && object1.y + object1.height > object2.y;
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
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i]->update(deltaTime);
	}
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->update(deltaTime);
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->update(deltaTime);
		if (bullets[i]->x < 0)
			bullets[i]->changeDirection("right");
		if (bullets[i]->x + bullets[i]->width > SCREEN_WIDTH)
			bullets[i]->changeDirection("left");
		if (bullets[i]->y < 0)
			bullets[i]->changeDirection("down");
		if (bullets[i]->y + bullets[i]->height > SCREEN_HEIGHT)
			bullets[i]->changeDirection("up");
	}

	for (int i = 0; i < blocks.size(); i++)
	{
		if (rectOverlap(*bullets[0], *blocks[i]))
		{
			bullets[0]->collided(*blocks[i]);
			bullets[0]->enterCollision();
		}
		else
		{
			bullets[0]->exitCollision();
		}
	}

	
	// only used to display FPS.
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
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i]->draw(window);
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->draw(window);
	}
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

void GameManager::removeFrom(std::vector<GameObject*>* list, GameObject* obj)
{
	auto& obj_list = *list;
	for (auto it = obj_list.begin(); it != obj_list.end(); )
	{
		if (*it == obj)
			it = obj_list.erase(it);
		else
			++it;
	}
}