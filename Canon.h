#pragma once

#include "GameObject.h"

#include <vector>

class Ball;

class Canon : public GameObject
{
	public:
		std::vector<Ball*> balls;

		Canon(float x, float y, sf::Color color, float w, float h);
		void postInit() override;

		void update(float dt) override;
};