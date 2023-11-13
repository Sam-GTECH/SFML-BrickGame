
#include "GameManager.h"

int main(int argc, char** argv)
{
    GameManager* game = new GameManager(60, true);

    game->gameLoop();

    delete game;

    return 0;
}