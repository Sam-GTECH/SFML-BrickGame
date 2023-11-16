#include "GameManager.h"
#include "GameObject.h"
#include "Canon.h"
#include "Brick.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

/// <summary>
/// Create a instance that manages a whole game
/// </summary>
/// <param name="limit">The framerate limit</param>
/// <param name="vsync">Decide if vsync is turn on or off</param>
GameManager::GameManager(int limit, bool vsync)
{
	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML", sf::Style::Close);
	window.setFramerateLimit(limit);
	window.setVerticalSyncEnabled(vsync);

	show_fps = font.loadFromFile("arial.ttf");

	if (show_fps)
	{
		text.setFont(font);
		text.setString("FPS: 0");
		text.setCharacterSize(16);
		text.setFillColor(sf::Color::White);
	}

	Input.game = this;

	GameObject* obj = new GameObject(100.f, 100.f, sf::Color::Blue, 50.f, 50.f);
	GameObject* obj2 = new GameObject(500.f, 400.f, sf::Color::Blue, 50.f, 50.f);
	Canon* caac = new Canon(640 / 2, 440, sf::Color::Cyan, 100.f, 50.f);
	addBlock(obj);
	//addBlock(obj2);
	addObject(caac);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 12; j++) {
			Brick* brick = new Brick(50+(50*j), 50+(40*i), sf::Color::White);
			addBlock(brick);
		}
	}

	Input.addInputEvent(this, sf::Event::MouseButtonPressed, [](GameManager* game, sf::Event::EventType event) -> bool {
		cout << "olee chitte" << endl;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			cout << "el rightto" << endl;
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			cout << "el leftto" << endl;
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
			cout << "ur mid" << endl;
		/*else if (event.mouseButton.button == sf::Mouse::XButton1)
			cout << "Gamer Mouse 1" << endl;
		else if (event.mouseButton.button == sf::Mouse::XButton2)
			cout << "Gamer Mouse 2" << endl;*/
		return true;
	});
	Input.addInputEvent(this, sf::Event::LostFocus, [](GameManager* game, sf::Event::EventType event) -> bool {cout << "olee chitte 2.0" << endl; return false; });
}

GameManager::~GameManager()
{
	window.~RenderWindow();
	for (int i = 0; i < blocks.size(); i++)
	{
		delete blocks[i];
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
	for (int i = 0; i < objects.size(); i++)
	{
		delete objects[i];
	}
}

bool GameManager::rectOverlap(GameObject& object1, GameObject& object2)
{
	return object1.x < object2.x + object2.width && object1.x + object1.width > object2.x && object1.y < object2.y + object2.height && object1.y + object1.height > object2.y;
}

bool GameManager::rectCircOverlap(GameObject& rect, GameObject& circ)
{
	float testX = circ.x;
	float testY = circ.y;
	if (circ.x < rect.x)         testX = rect.x;        // left edge
	else if (circ.x > rect.x + rect.width) testX = rect.x + rect.width;     // right edge

	if (circ.y < rect.y)         testY = rect.y;        // top edge
	else if (circ.y > rect.y + rect.height) testY = rect.y + rect.height;     // bottom edge

	float distX = circ.x - testX;
	float distY = circ.y - testY;
	float distance = sqrt((distX * distX) + (distY * distY));
	if (distance <= circ.getRadius()) {
		cout << "mdr ca touche" << endl;
		return true;
	}
	return false;
}

/// <summary>
/// The main loop that runs the game.
/// Closing or setting GameManager::run to false will stop it.
/// </summary>
void GameManager::gameLoop()
{
	while (run && window.isOpen())
	{
		if (window.hasFocus()) {
			sf::Event oEvent;
			while (window.pollEvent(oEvent))
			{
				if (oEvent.type == sf::Event::Closed)
				{
					window.close();
					run = false;
					break;
				}
				Input.handleEvents(oEvent);
			}
		}

		// If an event stopped the game, break from the game loop
		if (!run)
			break;

		update();

		window.clear();

		draw();

		deltaTime = deltaClock.restart().asSeconds();
	}
}

void GameManager::update()
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->update(deltaTime);
	}

	// collisions avec les bords de l'écran.
	for (int i = 0; i < bullets.size(); i++)
	{
		GameObject* curBullet = bullets[i];
		float curRadius = curBullet->getRadius();
		curBullet->update(deltaTime);
		if (curBullet->x - curRadius< 0)
			curBullet->changeDirection("right");
		if (curBullet->x + curRadius > SCREEN_WIDTH)
			curBullet->changeDirection("left");
		if (curBullet->y - curRadius < 0)
			curBullet->changeDirection("down");
		//if (curBullet->y + curRadius > SCREEN_HEIGHT)
			//curBullet->changeDirection("up");
	}

	for (int i = 0; i < blocks.size(); i++)
	{
		for (int j = 0; j < bullets.size(); j++)
		{
			if (rectCircOverlap(*blocks[i], *bullets[j]))
			{
				//bullets[j]->collided(*blocks[i]);
				bullets[j]->enterCollision();
			}
			else
			{
				bullets[j]->exitCollision();
			}
		}
	}
	
	// only used to display FPS.
	if (show_fps)
	{
		fpsTimer += deltaTime;
		fpsCount += 1.f;
		if (fpsTimer >= 1.f)
		{
			FPS = static_cast<float>(fpsCount) / fpsTimer;
			fpsCount = 0;
			fpsTimer -= 1.f;

			snprintf(fpsText, sizeof(fpsText), "FPS: %i", FPS);
			text.setString(fpsText);
		}
	}
}

void GameManager::draw()
{
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i]->draw(window);
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->draw(window);
	}
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->draw(window);
	}

	window.draw(text);

	window.display();
}

/// <summary>
/// Remove the GameObject obj from the vector list if it exists
/// </summary>
/// <param name="list">the vector to remove the GameObject from</param>
/// <param name="obj">The GameObject instance to remove from the vector list</param>
void GameManager::removeFrom(std::vector<GameObject*>* list, GameObject* obj)
{
	auto& obj_list = *list;
	for (auto it = obj_list.begin(); it != obj_list.end(); )
	{
		if (*it == obj)
			it = obj_list.erase(it);
		else
			++it;
	}
}

/// <summary>
/// Adds a GameObject to the objects table.
/// </summary>
/// <param name="obj">A GameObject instance</param>
void GameManager::addObject(GameObject* obj)
{
	objects.push_back(obj);
	addChild(obj);
}

/// <summary>
/// Adds a GameObject to the bullets table.
/// </summary>
/// <param name="obj">A GameObject instance</param>
void GameManager::addBullet(GameObject* obj)
{
	bullets.push_back(obj);
	addChild(obj);
}

/// <summary>
/// Adds a GameObject to the blocks table.
/// </summary>
/// <param name="obj">A GameObject instance</param>
void GameManager::addBlock(GameObject* obj)
{
	blocks.push_back(obj);
	addChild(obj);
}

/// <summary>
/// Gives an object their reference to the InputManager and the GameManager. Then calls their postInit() function.
/// </summary>
/// <param name="obj">A GameObject instance</param>
void GameManager::addChild(GameObject* obj)
{
	obj->Input = &Input;
	obj->Game = this;
	obj->postInit();
}