#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <iostream>
#include <vector>

int main(int argc, char** argv)
{
    sf::Clock deltaClock;
    float deltaTime = deltaClock.restart().asSeconds();
    int FPS = 0;
    float fpsCount = 0;
    float fpsTimer = 0;
    char fpsText[12];

    sf::RenderWindow oWindow(sf::VideoMode(640, 480), "SFML", sf::Style::Close);
    oWindow.setFramerateLimit(60);
    oWindow.setVerticalSyncEnabled(true);

    sf::Font font;
    bool show_fps = font.loadFromFile("arial.ttf");

    sf::Text text;
    text.setFont(font);
    text.setString("FPS: 0");
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);

    std::vector<GameObject*> objects;
    GameObject* obj = new GameObject(100.f, 100.f, sf::Color::Blue, 50.f, 50.f);
    GameObject* obj2 = new GameObject(320, 240.f, sf::Color::Green, 50.f);
    objects.push_back(obj);
    objects.push_back(obj2);

    float x = 100.f;

    //std::cout << obj->getRadius()

    obj->setRotation(45.f);
    float deg = 0.f;

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
        fpsTimer += deltaTime;
        fpsCount += 1.f;
        if (fpsTimer >= 1.f)
        {
            FPS = static_cast<float>(fpsCount) / fpsTimer;
            fpsCount = 0;
            fpsTimer -= 1.f;

            snprintf(fpsText, sizeof(fpsText), "FPS: %i", FPS);
            text.setString(fpsText);
        }

        //DRAW
        oWindow.clear();

        //std::cout << obj->getRotation() << std::endl;
        obj->setRotation(deg);
        deg += 150.f*deltaTime;

        //oWindow.draw(oCircle);
        //oWindow.draw(oRectangle);
        for (int i = 0; i < objects.size(); i++)
        {
            objects[i]->draw(oWindow);
        }

        oWindow.draw(text);

        oWindow.display();

        deltaTime = deltaClock.restart().asSeconds();
    }

    for (int i = 0; i < objects.size(); i++)
    {
        delete objects[i];
    }

    return 0;
}