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
  
		//update();
		void update(float deltaTime);
		void setVector(float x, float y);
		sf::Vector2f getPos();
		sf::Vector2f getSize();
		void draw(sf::RenderWindow& win);
		bool enterColision(GameObject object);
		void exitColision(GameObject object);
		void changeDirection(std::string side);
		void collided(GameObject& object);

	private:
		bool colision = false;
		int moveSpeed;
		sf::Shape* shape;
		sf::Vector2f speedVect;
};