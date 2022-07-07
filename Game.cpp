#include <stdio.h>

#include "Game.h"

Game* Game::s_pInstance = 0;

Game* Game::Instance()
{
    if (!s_pInstance)
        s_pInstance = new Game();
    return s_pInstance;
}

bool Game::Init(const char* title, int width, int height)
{
    m_pWindow = SDL_CreateWindow(title,
                                 SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED,
                                 width, height,
                                 SDL_WINDOW_SHOWN);
    if (!m_pWindow) {
        printf("Init error: %s\n", SDL_GetError());
        return false;
    }

    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
    if (!m_pRenderer) {
        printf("Init error: %s\n", SDL_GetError());
        return false;
    }

    m_bRunning = true;

    return true;
}

void Game::Clean()
{
    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);
    SDL_Quit();
}

void Game::HandleEvents()
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
        if (e.type == SDL_QUIT)
            m_bRunning = false;
}

void Game::Update()
{}

void Game::Render()
{}
