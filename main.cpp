
#include "GameManager.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char** argv)
{
    GameManager* game = new GameManager(60, true);

    game->gameLoop();

    delete game;

    return 0;
}