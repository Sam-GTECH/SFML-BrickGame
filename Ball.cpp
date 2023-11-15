#include "Ball.h"

Ball::Ball(float x, float y, sf::Color color, float r) : GameObject(x, y, color, r) {}

Ball::~Ball()
{
	Game->removeFrom(&Game->objects, this);
	canon->balls.clear();
}

void Ball::update(float deltaTime)
{
	GameObject::update(deltaTime);
	sf::Vector2u pos = Game->window.getSize();
	if (x > pos.x+30 || x < -30 || y > pos.y+30 || y < -30)
		delete this;
}