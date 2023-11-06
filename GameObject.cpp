#include "GameObject.h"
#include "SFML/Graphics.hpp"

GameObject::GameObject(float x, float y, sf::Color color, float r)
{
    //Création d'un cercle de radius r
    sf::CircleShape oCircle(r);
    //A la position x, y
    oCircle.setPosition(x, y);
    //Et de couleur color
    oCircle.setFillColor(color);

    shape = &oCircle;
}

GameObject::GameObject(float x, float y, sf::Color color, float w, float h)
{
    //Création d'un rectangle de taille 50, 50
    sf::RectangleShape = new oRectangle(sf::Vector2f(w, h));
    //A la position 100, 100
    oRectangle.setPosition(x, y);
    //Et de couleur rouge
    oRectangle.setFillColor(color);

    shape = &oRectangle;
}