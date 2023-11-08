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
		GameObject(float x, float y, sf::Color color, float w, float h);
		GameObject(float x, float y, sf::Color color, float r);

		//update();
		void update(float deltaTime);
		void setVector(float x, float y);
		sf::Vector2f getPos();
		sf::Vector2f getSize();
		void draw(sf::RenderWindow& win);
		bool rectOverlap(GameObject object);
		bool enterColision(GameObject object);
		void exitColision(GameObject object);

	private:
		float x = 1;
		float y = 1;
		float width = 1;
		float height = 1;
		bool colision;
		int moveSpeed;
		sf::Shape* shape;
		sf::Vector2f speedVect;
};