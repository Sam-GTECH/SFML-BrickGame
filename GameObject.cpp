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
    moveSpeed = 100;

    shape = oCircle;
}

GameObject::GameObject(float x, float y, sf::Color color, float w, float h)
    :width(w), height(h)
{
    //Création d'un rectangle de taille 50, 50
    sf::RectangleShape* oRectangle = new sf::RectangleShape(sf::Vector2f(w, h));
    //A la position 100, 100
    oRectangle->setPosition(x, y);
    //Et de couleur rouge
    oRectangle->setFillColor(color);
    //Avec un vecteur vitesse de 0
    speedVect.x = 0;
    speedVect.y = 0;
    moveSpeed = 100;

    shape = oRectangle;
}

void GameObject::update( float deltaTime)
{
    const sf::Vector2f* curPosition = &shape->getPosition();
    shape->setPosition(curPosition->x + speedVect.x * deltaTime * moveSpeed, curPosition->y + speedVect.y * deltaTime * moveSpeed);
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

void GameObject::draw(sf::RenderWindow& win)
{
    win.draw(*shape);
}

bool GameObject::rectOverlap(GameObject object)
{
    sf::Vector2f curPos = shape->getPosition();
    colision = true;
    return curPos.x < object.x + object.width && curPos.x + width > object.x&& curPos.y < object.y + object.height && curPos.y + height > object.y;
}

bool GameObject::enterColision(GameObject object)
{
    return colision ? rectOverlap(object) : false;
}

void GameObject::exitColision(GameObject object)
{
    if (colision)
        colision = rectOverlap(object);
}