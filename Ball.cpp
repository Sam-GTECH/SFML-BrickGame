#include "Ball.h"
#include <iostream>

Ball::Ball(float x, float y, sf::Color color, float r) : GameObject(x, y, color, r) {
	//sf::Color
}

void Ball::update(float deltaTime)
{
	cout << active << endl;
	if (active)
	{
		GameObject::update(deltaTime);
		sf::Vector2u pos = Game->window.getSize();
		if (x > pos.x + 30 || x < -30 || y > pos.y + 30 || y < -30)
			active = false;
	}
}