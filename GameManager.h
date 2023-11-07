#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class GameManager
{
	public:
		sf::RenderWindow window;
		
		bool run = false;

		GameManager(int limit, bool vsync);
		~GameManager();

		void gameLoop();
};