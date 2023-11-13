#pragma once


namespace sf 
{
	class Shape;
}

class InputManager;
class GameManager;

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class GameObject
{
	public:
		GameManager* Game;
		InputManager* Input;

		float x = 1;
		float y = 1;
		float width = 1;
		float height = 1;

		GameObject(float x, float y, sf::Color color, float w, float h);
		GameObject(float x, float y, sf::Color color, float r);
		GameObject();
		~GameObject();

		virtual void postInit();

		void setPosition(float x, float y);
		void setColor(sf::Color color);
		void setRotation(float deg);
		void setOrigin(float o_x, float o_y);

		float getRotation();
  
		virtual void update(float deltaTime);
		void setVector(float x, float y);
		sf::Vector2f getPos();
		sf::Vector2f getSize();
		sf::Vector2f getOrigin();
		void draw(sf::RenderWindow& win);
		bool rectOverlap(GameObject object);
		bool enterColision(GameObject object);
		void exitColision(GameObject object);
		void collide(std::string side);

	private:
		bool colision = false;
		int moveSpeed;
		sf::Shape* shape;
		sf::Vector2f speedVect;
};