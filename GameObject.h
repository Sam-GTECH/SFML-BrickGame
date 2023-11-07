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

		//update();
		void update(float deltaTime);
		void setVector(float x, float y);
		sf::Vector2f getPos();
		void draw(sf::RenderWindow& win);
		void collide(std::string side);
		//void setColor(float x, float y);

	private:
		sf::Shape* shape;
		sf::Vector2f speedVect;
};