#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_image.h>

#include "TextureManager.h"
#include "InputHandler.h"
#include "MenuState.h"

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
    srand(time(0));

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "Init error: " << SDL_GetError() << std::endl;
        return false;
    }

    m_pWindow = SDL_CreateWindow(title,
                                 SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED,
                                 width, height,
                                 SDL_WINDOW_SHOWN);
    if (!m_pWindow)
    {
        std::cout << "Init error: " << SDL_GetError() << std::endl;
        return false;
    }

    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
    if (!m_pRenderer)
    {
        std::cout << "Init error: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_SetRenderDrawColor(m_pRenderer, 0x00, 0x00, 0x00, 255);

    m_pCurrentState = new MenuState();
    m_pNextState = 0;

    m_bRunning = true;

    return true;
}

void Game::Clean()
{
    if (m_pCurrentState)
        delete m_pCurrentState;
    if (m_pNextState)
        delete m_pNextState;

    TextureManager::Instance()->Clean();
    InputHandler::Instance()->Clean();

    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);
    IMG_Quit();
    SDL_Quit();
}

void Game::HandleEvents()
{
    InputHandler::Instance()->Update();
}

void Game::Update()
{
    if (m_pNextState)
    {
        delete m_pCurrentState;
        m_pCurrentState = m_pNextState;
        m_pNextState = 0;
    }

    m_pCurrentState->Update();
}

void Game::Render()
{
    SDL_RenderClear(m_pRenderer);
    m_pCurrentState->Render();
    SDL_RenderPresent(m_pRenderer);
}
