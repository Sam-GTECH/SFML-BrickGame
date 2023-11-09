#include "InputManager.h"
#include "SFML/System/Vector2.hpp"
#include <iostream>
using namespace std;

InputManager::InputManager() {}

void InputManager::addInputEvent(sf::Event::EventType event, bool (*func)(sf::Event::EventType event))
{
	callbacks[event].push_back(func);
}

void InputManager::handleEvents(sf::Event event)
{
	if (callbacks[event.type].size() > 0)
	{
		for (int i = 0; i < callbacks[event.type].size(); i++)
		{
			if (!callbacks[event.type][i](event.type))
				callbacks[event.type].erase(callbacks[event.type].begin() + i);
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