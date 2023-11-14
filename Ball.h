#pragma once

#include "GameObject.h"

class Ball : public GameObject
{
	public:
		Ball(float x, float y, sf::Color color, float r);

		void update(float deltaTime) override;

	private:

};