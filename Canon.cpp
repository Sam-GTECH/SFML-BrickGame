#include "Canon.h"
#include "Ball.h"
#include <iostream>
#include "math.h"
using namespace std;

Canon::Canon(float x, float y, sf::Color color, float w, float h) : GameObject(x, y, color, w, h)
{
	setRotation(90);
}

void Canon::postInit()
{
	Input->addInputEvent(this, sf::Event::MouseButtonPressed, [](GameObject* obj, sf::Event::EventType event) -> bool {
		cout << "SHOOT THE TURTLE AND PUT HIM IN THE RHUM!!" << endl;
		Canon* canon = dynamic_cast<Canon*>(obj);
		if (!canon)
			return true;
		else if (canon->ball->active)
			return true;
		
		sf::Vector2f pos = canon->getPos();
		float rot = canon->getRotation() * ((atan(1) * 4) / 180);
		float x = pos.x + canon->width / 2 * cos(rot);
		float y = pos.y + (canon->height) * sin(rot);

		canon->ball->setPosition(x, y);
		canon->ball->setVector(cos(rot), sin(rot));
		
		canon->ball->active = true;
		return true;
	});

	Ball* b = new Ball(-999, -999, sf::Color::Red, 10);
	b->canon = this;
	ball = b;
	Game->addBullet(ball);
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

	sf::Vector2u size = Game->window.getSize();

	sf::Vector2f vect = pos + orig_shape;
	float adj = mouse.x+50 - vect.x;
	float opp = mouse.y - vect.y;

	float angle = math::angle(adj, opp, true) + 90;
	if (mouse.x < size.x/2 && angle < 190)
		angle = 190;
	else if (mouse.x > size.x/2 && angle > -10)
		angle = -10;
	setRotation(angle);

	if (ball->active)
		setColor(sf::Color(150, 150, 150, 255));
	else
		setColor(sf::Color::Cyan);
}