#pragma once
#include <cmath>
#include <SFML\System\Vector2.hpp>

namespace math
{
	extern double pi;

	float angle(float cood1, float cood2, bool turn_to_degrees);

	void normalizeVector(sf::Vector2f* vector);
}