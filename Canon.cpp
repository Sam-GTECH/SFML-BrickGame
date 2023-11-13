#include "Canon.h"
#include <iostream>
#include <cmath>
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
		obj->setColor(sf::Color::White);
		sf::Vector2f pos = obj->getPos();
		float rot = obj->getRotation() * ((atan(1) * 4) / 180);
		float x = pos.x + obj->width/2 * cos(rot);
		float y = pos.y + (obj->height) * sin(rot);
		GameObject* ball = new GameObject(x, y, sf::Color::Red, 10);
		ball->setVector(cos(rot), sin(rot));
		obj->Game->addChild(ball);
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

	double pi = atan(1)*4;
	float angle = -atan2(adj, opp);
	float deg_angle = angle * (180 / pi);
	/*if (deg_angle > -10)
		deg_angle = -10;
	else if (deg_angle < -170)
		deg_angle = -170;*/
	cout << angle << " || " << deg_angle << " (" << mouse.x << ", " << mouse.y << ")" << endl;
	setRotation(deg_angle+90);
}