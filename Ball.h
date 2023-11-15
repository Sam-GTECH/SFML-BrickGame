#pragma once

#include "GameObject.h"
#include "GameManager.h"
#include "Canon.h"

class Ball : public GameObject
{
	public:
		Canon* canon;

		Ball(float x, float y, sf::Color color, float r);
		~Ball();

		void update(float deltaTime) override;

	private:

};