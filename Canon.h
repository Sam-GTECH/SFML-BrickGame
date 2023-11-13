#pragma once

#include "GameObject.h"

#include "GameManager.h"
#include "InputManager.h"

class Canon : public GameObject
{
	public:
		Canon(float x, float y, sf::Color color, float w, float h);
		void postInit() override;

		void update(float dt) override;
};