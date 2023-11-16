#pragma once

#include "GameObject.h"
#include "GameManager.h"

class Brick : public GameObject
{
	public:
		Brick(float x, float y, sf::Color color);
		Brick(float x, float y, sf::Color color, float w, float h);
		~Brick();

		void update(float deltaTime) override;

	private:
		int health = 1;
};