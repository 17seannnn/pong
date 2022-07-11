#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#include "GameState.h"

class Game { 
    static Game* s_pInstance;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    GameState* m_pCurrentState;
    GameState* m_pNextState;

    bool m_bRunning;
public:
    static Game* Instance();

    bool Init(const char* title, int width, int height);
    // Use it to quit from running game, clean after
    void Quit() { m_bRunning = false; }
    void Clean();

    bool Running() const { return m_bRunning; }
    void HandleEvents();
    void Update();
    void Render();
private:
    Game() {}
    ~Game() {}
};

#endif
