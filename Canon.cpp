#include "Canon.h"
#include "Ball.h"
#include <iostream>
#include "math.hpp"
using namespace std;

Canon::Canon(float x, float y, sf::Color color, float w, float h) : GameObject(x, y, color, w, h)
{
	cout << "canon" << endl;
	setRotation(90);
}

void Canon::postInit()
{
	Input->addInputEvent(this, sf::Event::MouseButtonPressed, [](GameObject* obj, sf::Event::EventType event) -> bool {
		cout << "SHOOT THE TURTLE AND PUT HIM IN THE RHUM!!" << endl;
		Canon* canon = dynamic_cast<Canon*>(obj);
		if (!canon)
			return true;
		else if (canon->balls.size() > 0)
			return true;
		sf::Vector2f pos = obj->getPos();
		float rot = obj->getRotation() * ((atan(1) * 4) / 180);
		float x = pos.x + obj->width/2 * cos(rot);
		float y = pos.y + (obj->height) * sin(rot);
		
		Ball* ball = new Ball(x, y, sf::Color::Red, 10);
		ball->setVector(cos(rot), sin(rot));
		obj->Game->addChild(ball);
		canon->balls.push_back(ball);
		return true;
	});
}

float getVectPos(sf::Vector2f vect)
{
	return sqrt((vect.x * vect.x) + (vect.y * vect.y));
}
void Canon::update(float dt)
{
	//cout << "canonbaaaaaaaaaaaaaaaaaaall" << endl;
	sf::Vector2i mouse = Input->getMousePos(Game->window, false);
	sf::Vector2f pos = getPos();
	sf::Vector2f orig_shape = getOrigin();

	sf::Vector2f vect = pos + orig_shape;
	float adj = mouse.x - vect.x;
	float opp = mouse.y - vect.y;

	/*if (deg_angle > -10)
		deg_angle = -10;
	else if (deg_angle < -170)
		deg_angle = -170;*/
	//cout << angle << " || " << deg_angle << " (" << mouse.x << ", " << mouse.y << ")" << endl;
	setRotation(math::angle(adj, opp, true) + 90);

	cout << balls.size() << endl;
	if (balls.size() == 1)
		setColor(sf::Color(150, 150, 150, 255));
	else
		setColor(sf::Color::Cyan);
}