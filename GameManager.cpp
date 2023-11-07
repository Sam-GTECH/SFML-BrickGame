#include "GameManager.h"

GameManager::GameManager(int limit, bool vsync)
{
	window.create(sf::VideoMode(640, 480), "SFML", sf::Style::Close);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
}

GameManager::~GameManager()
{

}

void GameManager::gameLoop()
{
	while (run)
	{

	}
}