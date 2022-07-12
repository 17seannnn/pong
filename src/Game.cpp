#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "TextureManager.h"
#include "InputHandler.h"
#include "PlayState.h"

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

    TextureManager::Instance()->SetRenderer(m_pRenderer);
    TextureManager::Instance()->Load("assets/divider.png", TEXTURE_DIVIDER);
    TextureManager::Instance()->Load("assets/ball.png", TEXTURE_BALL);
    TextureManager::Instance()->Load("assets/player.png", TEXTURE_PLAYER);
    TextureManager::Instance()->Load("assets/numbers.png", TEXTURE_NUMBERS);

    m_pCurrentState = new PlayState();
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
    SDL_Quit();
}

void Game::HandleEvents()
{
    InputHandler::Instance()->Update();
}

void Game::Update()
{
    m_pCurrentState->Update();

    if (m_pNextState)
    {
        delete m_pCurrentState;
        m_pCurrentState = m_pNextState;
        m_pNextState = 0;
    }
}

void Game::Render()
{
    SDL_RenderClear(m_pRenderer);
    m_pCurrentState->Render();
    SDL_RenderPresent(m_pRenderer);
}
