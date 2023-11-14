#include "GameObject.h"
#include "SFML/Graphics.hpp"

#include <string>
#include <cmath>

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

GameObject::GameObject(float x, float y, sf::Color color, float w, float h)
    :width(w), height(h)
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
        speedVect.y = 1;
    else if (side == "up")
        speedVect.y = -1;
    else if (side == "right")
        speedVect.x = 1;
    else if (side == "left")
        speedVect.x = -1;
}

void GameObject::collided(GameObject& object)
{
    if (collision)
    {
        return;
    }
    // Most of this stuff would probably be good to keep stored inside the player
    // along side their x and y position. That way it doesn't have to be recalculated
    // every collision check
    float playerHalfW = this->width / 2;
    float playerHalfH = this->height / 2;
    float enemyHalfW = object.width / 2;
    float enemyHalfH = object.height / 2;
    float playerCenterX = this->x + this->width / 2;
    float playerCenterY = this->y + this->height / 2;
    float enemyCenterX = object.x + object.width / 2;
    float enemyCenterY = object.y + object.height / 2;

    // Calculate the distance between centers
    float diffX = playerCenterX - enemyCenterX;
    float diffY = playerCenterY - enemyCenterY;

    // Calculate the minimum distance to separate along X and Y
    float minXDist = playerHalfW + enemyHalfW;
    float minYDist = playerHalfH + enemyHalfH;

    // Calculate the depth of collision for both the X and Y axis
    float depthX = diffX > 0 ? minXDist - diffX : -minXDist - diffX;
    float depthY = diffY > 0 ? minYDist - diffY : -minYDist - diffY;

    // Now that you have the depth, you can pick the smaller depth and move
    // along that axis.
    if (depthX != 0 && depthY != 0) {
        if (abs(depthX) < abs(depthY)) {
            // Collision along the X axis. React accordingly
            if (depthX > 0) {
                changeDirection("right");
            }
            else {
                changeDirection("left");
            }
        }
        else {
            // Collision along the Y axis.
            if (depthY > 0) {
                changeDirection("down");
            }
            else {
                changeDirection("up");
            }
        }
    }
}