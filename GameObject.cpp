#include "GameObject.h"
#include "SFML/Graphics.hpp"

GameObject::GameObject(float x, float y, sf::Color color, float r)
{
    sf::CircleShape* oCircle = new sf::CircleShape(r);
    oCircle->setPosition(x, y);
    oCircle->setFillColor(color);

    oCircle->setOrigin(sf::Vector2f(.5f * (r * 2), .5f * (r * 2)));

    shape = oCircle;

    x = x;
    y = y;
    width = r*2;
    height = r*2;
}

GameObject::GameObject(float x, float y, sf::Color color, float w, float h)
{
    sf::RectangleShape* oRectangle = new sf::RectangleShape(sf::Vector2f(w, h));
    oRectangle->setPosition(x, y);
    oRectangle->setFillColor(color);

    oRectangle->setOrigin(sf::Vector2f(.5f*w, .5f*h));

    shape = oRectangle;

    x = x;
    y = y;
    width = w;
    height = h;
}

GameObject::~GameObject()
{
    delete shape;
}

///////////////////////// SETTERS

void GameObject::setPosition(float x, float y)
{
    shape->setPosition(x, y);
}

void GameObject::setColor(sf::Color color)
{
    shape->setFillColor(color);
}

void GameObject::setRotation(float deg)
{
    shape->setRotation(deg);
}

// \param o_x origin point for X (0-1)
// \param o_y origin point for Y (0-1)
void GameObject::setOrigin(float o_x, float o_y)
{
    shape->setOrigin(o_x*width, o_y*height);
}

///////////////////////// GETTERS

float GameObject::getRotation()
{
    return shape->getRotation();
}

//////////////////////////// GAME EVENTS

void GameObject::draw(sf::RenderWindow& win)
{
    win.draw(*shape);
}