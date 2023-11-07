#include <SFML/Graphics.hpp>
#include "GameObject.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char** argv)
{
    sf::Clock deltaClock;
    float deltaTime = deltaClock.restart().asSeconds();

    //Création d'une fenêtre
    sf::RenderWindow oWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML");

    GameObject* obj = new GameObject(50.f, 50.f, sf::Color::Blue, 50.f, 60.f);
    obj->setVector(1, -1);

    //GameLoop
    while (oWindow.isOpen())
    {
        //EVENT
        sf::Event oEvent;
        while (oWindow.pollEvent(oEvent))
        {
            if (oEvent.type == sf::Event::Closed)
                oWindow.close();
        }

        //UPDATE
        obj->update(deltaTime);
        sf::Vector2f curPos = obj->getPos();
        printf("%f\n", curPos.y);
        if (curPos.y < 0)
        {
            obj->collide("up");
        }
        if (curPos.y > SCREEN_HEIGHT)
        {
            obj->collide("down");
        }
        if (curPos.x < 0)
        {
            obj->collide("left");
        }
        if (curPos.x > SCREEN_WIDTH)
        {
            obj->collide("right");
        }

        //DRAW
        oWindow.clear();
        obj->draw(oWindow);

        //oWindow.draw(oCircle);
        //oWindow.draw(oRectangle);

        oWindow.display();
        deltaTime = deltaClock.restart().asSeconds();
    }

    return 0;
}