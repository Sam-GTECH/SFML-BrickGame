#include "GameObject.h"
#include "SFML/Graphics.hpp"

#include <string>

GameObject::GameObject(float x, float y, sf::Color color, float r)
{
    //Création d'un cercle de radius r
    sf::CircleShape* oCircle = new sf::CircleShape(r);
    //A la position x, y
    oCircle->setPosition(x, y);
    //Et de couleur color
    oCircle->setFillColor(color);
    //Avec un vecteur vitesse de 0
    speedVect.x = 0;
    speedVect.y = 0;

    shape = oCircle;
}

GameObject::GameObject(float x, float y, sf::Color color, float w, float h)
{
    //Création d'un rectangle de taille 50, 50
    sf::RectangleShape* oRectangle = new sf::RectangleShape(sf::Vector2f(w, h));
    //A la position 100, 100
    oRectangle->setPosition(x, y);
    //Et de couleur rouge
    oRectangle->setFillColor(color);

    shape = oRectangle;
}

void GameObject::update( float deltaTime)
{
    const sf::Vector2f* curPosition = &shape->getPosition();
    shape->setPosition(curPosition->x + speedVect.x * deltaTime * 100, curPosition->y + speedVect.y * deltaTime * 100);
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

void GameObject::draw(sf::RenderWindow& win)
{
    win.draw(*shape);
}

void GameObject::collide(std::string side)
{
    if (side == "left")
        speedVect.x = 1;
    if (side == "right")
        speedVect.x = -1;
    if (side == "up")
        speedVect.y = 1;
    if (side == "down")
        speedVect.y = -1;
}