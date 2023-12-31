#include "GameObject.h"
#include "SFML/Graphics.hpp"

#include <string>
#include <cmath>

// Circle shape
GameObject::GameObject(float x, float y, sf::Color color, float r)
{
    sf::CircleShape* oCircle = new sf::CircleShape(r);
    oCircle->setPosition(x, y);
    oCircle->setFillColor(color);
    //Avec un vecteur vitesse de 0
    speedVect.x = 0;
    speedVect.y = 0;
    moveSpeed = 100;

    oCircle->setOrigin(sf::Vector2f(.5f * (r * 2), .5f * (r * 2)));

    shape = oCircle;

    x = x;
    y = y;
    width = r*2;
    height = r * 2;
}

// Rectangle shape
GameObject::GameObject(float x, float y, sf::Color color, float w, float h)
    :x(x), y(y), width(w), height(h)
{
    sf::RectangleShape* oRectangle = new sf::RectangleShape(sf::Vector2f(w, h));
    oRectangle->setPosition(x, y);
    oRectangle->setFillColor(color);
    //Avec un vecteur vitesse de 0
    speedVect.x = 0;
    speedVect.y = 0;
    moveSpeed = 100;

    oRectangle->setOrigin(sf::Vector2f(.5f*w, .5f*h));

    shape = oRectangle;

    x = x;
    y = y;
    width = w;
    height = h;
}
GameObject::GameObject() {}

GameObject::~GameObject()
{
    delete shape;
}

void GameObject::postInit() {}

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

sf::Vector2f GameObject::getOrigin()
{
    return shape->getOrigin();
}

//////////////////////////// GAME EVENTS

void GameObject::draw(sf::RenderWindow& win)
{
    win.draw(*shape);
}

void GameObject::update( float deltaTime)
{
    const sf::Vector2f* curPosition = &shape->getPosition();
    float newPosX = curPosition->x + speedVect.x * deltaTime * moveSpeed;
    float newPosY = curPosition->y + speedVect.y * deltaTime * moveSpeed;
    x = newPosX;
    y = newPosY;
    shape->setPosition(newPosX, newPosY);
}

void GameObject::setVector(float x, float y)
{
    speedVect.x = x;
    speedVect.y = y;
}

sf::Vector2f GameObject::getPos()
{
    return shape->getPosition();
}

float GameObject::getRadius()
{
    return width/2;
}

sf::Vector2f GameObject::getSize()
{
    return sf::Vector2f(width, height);
}

void GameObject::enterCollision()
{
    collision = true;
}

void GameObject::exitCollision()
{
    collision = false;
}

void GameObject::changeDirection(std::string side)
{
    if (side == "down")
    {
        if (speedVect.y < 0) speedVect.y = speedVect.y * -1;
    }
    else if (side == "up")
    {
        if (speedVect.y > 0) speedVect.y = speedVect.y * -1;
    }
    else if (side == "right")
    {
        if (speedVect.x < 0) speedVect.x = speedVect.x * -1;
    }
    else if (side == "left")
    {
        if (speedVect.x > 0) speedVect.x = speedVect.x * -1;
    }
}