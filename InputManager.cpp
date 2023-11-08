#include "InputManager.h"
#include "SFML/System/Vector2.hpp"
#include <iostream>
using namespace std;

InputManager::InputManager()
{

}

bool InputManager::addInputEvent(sf::Event::EventType event, bool (*func)())
{
	callbacks[event].push_back(func);
	return false;
}

void InputManager::handleEvents(sf::Event event)
{
	if (callbacks[event.type].size() > 0)
		for (int i = 0; i < callbacks[event.type].size(); i++)
		{
			if (!callbacks[event.type][i]())
				callbacks[event.type].erase(callbacks[event.type].begin()+i);
		}
}

sf::Vector2i InputManager::getMousePos()
{
	sf::Vector2i m = mouse.getPosition();
	int x = m.x;
	int y = m.y;
	return sf::Vector2i(x, y);
}