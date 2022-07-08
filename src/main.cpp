#include "Game.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main()
{
    if (!Game::Instance()->Init("Pong", 1280, 720))
        return 1;

    while (Game::Instance()->Running())
    {
        int frameStart = SDL_GetTicks();

        Game::Instance()->HandleEvents();
        Game::Instance()->Update();
        Game::Instance()->Render();

        int frameDiff = SDL_GetTicks() - frameStart;
        if (frameDiff < DELAY_TIME)
            SDL_Delay(DELAY_TIME - frameDiff);
    }

    Game::Instance()->Clean();
}
