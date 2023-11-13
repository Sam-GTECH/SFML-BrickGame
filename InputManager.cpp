#include "InputManager.h"
#include "SFML/System/Vector2.hpp"
#include <iostream>
using namespace std;

InputManager::InputManager() {}

void InputManager::addInputEvent(GameManager* obj, sf::Event::EventType event, bool (*func)(GameManager* game, sf::Event::EventType event))
{
	game_callbacks[event].push_back(func);
}

void InputManager::addInputEvent(GameObject* obj, sf::Event::EventType event, bool (*func)(GameObject* obj, sf::Event::EventType event))
{
	obj_callbacks[event].push_back(func);
	objects_id.push_back(obj);
}

void InputManager::handleEvents(sf::Event event)
{
	if (game_callbacks[event.type].size() > 0)
	{
		for (int i = 0; i < game_callbacks[event.type].size(); i++)
		{
			if (!game_callbacks[event.type][i](game, event.type))
				game_callbacks[event.type].erase(game_callbacks[event.type].begin() + i);
		}
	}
	if (obj_callbacks[event.type].size() > 0)
	{
		for (int i = 0; i < obj_callbacks[event.type].size(); i++)
		{
			if (!obj_callbacks[event.type][i](objects_id[i], event.type))
			{
				obj_callbacks[event.type].erase(obj_callbacks[event.type].begin() + i);
				objects_id.erase(objects_id.begin() + i);
			}
		}
	}
}

sf::Vector2i InputManager::getMousePos(sf::RenderWindow& window, bool clamp)
{
	sf::Vector2i m = mouse.getPosition();
	sf::Vector2i w = window.getPosition();
	int x = (m.x - w.x)-7;
	int y = (m.y - w.y)-30;
	if (clamp)
	{
		if (x < 0)
			x = 0;
		else if (x > 640)
			x = 640;
		if (y < 0)
			y = 0;
		else if (y > 480)
			y = 480;
	}
	return sf::Vector2i(x, y);
}