#include "Brick.h"

Brick::Brick(float x, float y, sf::Color color) : GameObject(x, y, color, 40, 20)
{
}

Brick::Brick(float x, float y, sf::Color color, float w, float h) : GameObject(x, y, color, w, h)
{

}
Brick::~Brick()
{
	Game->removeFrom(&Game->blocks, this);
}

void Brick::update(float deltaTime)
{
	GameObject::update(deltaTime);

	if (health <= 0)
		delete this;
}