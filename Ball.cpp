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
	//sf::Vector2i Game->window->getPosition()
	//if (x > Game)
}