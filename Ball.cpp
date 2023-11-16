#include "Ball.h"

#include "GameManager.h"
#include "Canon.h"

Ball::Ball(float x, float y, sf::Color color, float r) : GameObject(x, y, color, r) {}

Ball::~Ball()
{
	Game->removeFrom(&Game->objects, this);
	canon->balls.clear();
}

void Ball::update(float deltaTime)
{
	GameObject::update(deltaTime);
	bbRect = GameObject(x, y, sf::Color::Blue, width, height);
	sf::Vector2u pos = Game->window.getSize();
	if (x > pos.x+30 || x < -30 || y > pos.y+30 || y < -30)
		delete this;
}

void Ball::collided(GameObject& object)
{
    float playerHalfW = bbRect.width / 2;
    float playerHalfH = bbRect.height / 2;
    float enemyHalfW = object.width / 2;
    float enemyHalfH = object.height / 2;
    float playerCenterX = bbRect.x + playerHalfW;
    float playerCenterY = bbRect.y + playerHalfH;
    float enemyCenterX = object.x + enemyHalfW;
    float enemyCenterY = object.y + enemyHalfH;

    float diffX = playerCenterX - enemyCenterX;
    float diffY = playerCenterY - enemyCenterY;

    float minXDist = playerHalfW + enemyHalfW;
    float minYDist = playerHalfH + enemyHalfH;

    float depthX = diffX > 0 ? minXDist - diffX : -minXDist - diffX;
    float depthY = diffY > 0 ? minYDist - diffY : -minYDist - diffY;

    if (depthX != 0 && depthY != 0) {
        if (abs(depthX) < abs(depthY)) {
            if (depthX > 0) {
                changeDirection("right");
            }
            else {
                changeDirection("left");
            }
        }
        else {
            if (depthY > 0) {
                changeDirection("down");
            }
            else {
                changeDirection("up");
            }
        }
    }
}