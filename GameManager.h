#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include "InputManager.h"

class GameObject;

//namespace sf {
//	class Vector2i;
//}

class GameManager
{
	sf::Clock deltaClock;
	int FPS = 0;
	float fpsCount = 0;
	float fpsTimer = 0;
	char fpsText[12];
	bool show_fps = false;

	sf::Font font;
	sf::Text text;

	public:
		sf::RenderWindow window;
		InputManager Input;
		std::vector<GameObject*> objects;

		float deltaTime = deltaClock.restart().asSeconds();
		
		bool run = true;

		GameManager(int limit, bool vsync);
		~GameManager();

		void gameLoop();
		void addChild(GameObject* obj);

	private:
		void update();
		void draw();
};