#pragma once


namespace sf 
{
	class Shape;
}

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class GameObject
{
	public:

		float x = 1;
		float y = 1;
		float width = 1;
		float height = 1;

		GameObject(float x, float y, sf::Color color, float w, float h);
		GameObject(float x, float y, sf::Color color, float r);
		~GameObject();

		void setPosition(float x, float y);
		void setColor(sf::Color color);
		void setRotation(float deg);
		void setOrigin(float o_x, float o_y);

		float getRotation();

		void update();
		void draw(sf::RenderWindow& win);

	private:
		sf::Shape* shape;
};