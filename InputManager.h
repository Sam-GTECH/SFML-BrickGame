#pragma once
#include <map>
#include <vector>
#include "SFML/Window/Event.hpp"
#include "SFML/System/Vector2.hpp"
using namespace std;

class InputManager
{
	map<sf::Event::EventType, vector<bool (*)()>> callbacks;
	sf::Mouse mouse;
	sf::Keyboard keyboard;
	sf::Joystick joystick;

	public:
		InputManager();

		bool addInputEvent(sf::Event::EventType event, bool (*func)());

		void handleEvents(sf::Event event);

		sf::Vector2i getMousePos();
};