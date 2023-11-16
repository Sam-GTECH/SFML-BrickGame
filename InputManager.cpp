#include "InputManager.h"
#include "SFML/System/Vector2.hpp"
#include <iostream>
using namespace std;

InputManager::InputManager() {}

/// <summary>
/// Register an input event from the GameManager
/// </summary>
/// <param name="obj">The instance of the GameManager, will be passed to the function</param>
/// <param name="event">The event that should cause the function to be called</param>
/// <param name="func">A lambda function that will be called when the event occures. If it returns false, the event will be removed.</param>
void InputManager::addInputEvent(GameManager* obj, sf::Event::EventType event, bool (*func)(GameManager* game, sf::Event::EventType event))
{
	game_callbacks[event].push_back(func);
}

/// <summary>
/// Register an input event for a GameObject
/// </summary>
/// <param name="obj">The object concerned by the event, will be passed to the function</param>
/// <param name="event">The event that should cause the function to be called</param>
/// <param name="func">A lambda function that will be called when the event occures. If it returns false, the event will be removed.</param>
void InputManager::addInputEvent(GameObject* obj, sf::Event::EventType event, bool (*func)(GameObject* obj, sf::Event::EventType event))
{
	obj_callbacks[event].push_back(func);
	objects_id.push_back(obj);
}

/// <summary>
/// Checks if any input events should be called based on the current event and then remove them if necessery
/// </summary>
/// <param name="event">An instance of sf::Event</param>
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

/// <summary>
/// Returns the position of the mouse
/// </summary>
/// <param name="window">An instance of sf::RenderWindow</param>
/// <param name="clamp">If true, the values will be clamped between 0 and the window's width and height.</param>
/// <returns></returns>
sf::Vector2i InputManager::getMousePos(sf::RenderWindow& window, bool clamp)
{
	sf::Vector2i m = mouse.getPosition();
	sf::Vector2i w = window.getPosition();
	sf::Vector2u s = window.getSize();
	int x = (m.x - w.x)-7;
	int y = (m.y - w.y)-30;
	if (clamp)
	{
		if (x < 0)
			x = 0;
		else if (x > s.x)
			x = s.x;
		if (y < 0)
			y = 0;
		else if (y > s.y)
			y = s.y;
	}
	return sf::Vector2i(x, y);
}