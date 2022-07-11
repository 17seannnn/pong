#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#include "Vector.h"
#include "Player.h"
#include "Ball.h"

#include "Object.h"

class Game { 
    static Game* s_pInstance;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    bool m_bRunning;

    int m_score1, m_score2;

    Ball* m_pBall;
    Player* m_pPlayer1;
    Player* m_pPlayer2;

    Vector<Object*> m_objects;
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

    void DrawScores();
};

#endif
