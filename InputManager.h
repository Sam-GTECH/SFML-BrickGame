#pragma once
#include <map>
#include <vector>
#include "SFML/Window/Event.hpp"
#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
using namespace std;

class InputManager
{
	map<sf::Event::EventType, vector<bool (*)(sf::Event::EventType event)>> callbacks;
	sf::Mouse mouse;
	sf::Keyboard keyboard;
	sf::Joystick joystick;

	public:
		InputManager();

		void addInputEvent(sf::Event::EventType event, bool (*func)(sf::Event::EventType event));

		void handleEvents(sf::Event event);

		sf::Vector2i getMousePos(sf::RenderWindow& window, bool clamp);
};