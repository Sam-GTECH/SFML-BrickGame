#pragma once
#include <map>
#include <vector>
#include "SFML/Window/Event.hpp"
#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
using namespace std;

class GameObject;
class GameManager;

class InputManager
{
	map<sf::Event::EventType, vector<bool (*)(GameObject* obj, sf::Event::EventType event)>> obj_callbacks;
	map<sf::Event::EventType, vector<bool (*)(GameManager* game, sf::Event::EventType event)>> game_callbacks;
	vector<GameObject*> objects_id;

	sf::Mouse mouse;
	sf::Keyboard keyboard;
	sf::Joystick joystick;

	public:
		GameManager* game;

		InputManager();

		void addInputEvent(GameObject* obj, sf::Event::EventType event, bool (*func)(GameObject* obj, sf::Event::EventType event));
		void addInputEvent(GameManager* obj, sf::Event::EventType event, bool (*func)(GameManager* game, sf::Event::EventType event));

		void handleEvents(sf::Event event);

		sf::Vector2i getMousePos(sf::RenderWindow& window, bool clamp);
};