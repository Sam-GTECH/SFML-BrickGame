#include "Canon.h"
#include <iostream>
#include <cmath>
using namespace std;

Canon::Canon(float x, float y, sf::Color color, float w, float h) : GameObject(x, y, color, w, h)
{
	cout << "canon" << endl;
	setRotation(90);
}

void Canon::update(float dt)
{
	sf::Vector2i mouse = input->getMousePos(game->window, true);
	setRotation(atan2(y - mouse.y, x - mouse.x));
}