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
	Input->addInputEvent(sf::Event::MouseButtonPressed, [](sf::Event::EventType event) -> bool {
		cout << "SHOOT THE TURTLE AND PUT HIM IN THE RHUM!!" << endl;
		return true;
	});
}

void Canon::update(float dt)
{
	//cout << "canonbaaaaaaaaaaaaaaaaaaall" << endl;
	sf::Vector2i mouse = Input->getMousePos(Game->window, false);
	double pi = 3.141592;
	float angle = atan2((mouse.y - 250) - y, (mouse.x - 340) - x);
	float deg_angle = angle * (180 / pi);
	if (deg_angle > -10)
		deg_angle = -10;
	else if (deg_angle < -170)
		deg_angle = -170;
	cout << angle << " || " << deg_angle << " (" << mouse.x << ", " << mouse.y << ")" << endl;
	setRotation(deg_angle);
}