#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <vector>

#include "Object.h"

class Game { 
    static Game* s_pInstance;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    bool m_bRunning;

    std::vector<Object*> m_objects;
public:
    static Game* Instance();

    bool Init(const char* title, int width, int height);
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
