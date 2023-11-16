#pragma once

#include "GameObject.h"

class Canon;

class Ball : public GameObject
{
	public:
		GameObject bbRect;
		Canon* canon;

		Ball(float x, float y, sf::Color color, float r);
		~Ball();

		void update(float deltaTime) override;
		void collided(GameObject& object) override;

	private:

};