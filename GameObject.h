#pragma once


namespace sf 
{
	class Shape;
}

#include <SFML/Graphics/Color.hpp>

class GameObject
{
	public:

		float x;
		float y;
		float width = 1;
		float height = 1;

		GameObject(float x, float y, sf::Color color, float w, float h);
		GameObject(float x, float y, sf::Color color, float r);

		//update();
		//draw(sf::RenderWindow win);

	private:
		sf::Shape* shape;
};