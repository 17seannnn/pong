#include <iostream>

#include "TextureManager.h"
#include "InputHandler.h"
#include "Player.h"

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

    m_bRunning = true;

    TextureManager::Instance()->SetRenderer(m_pRenderer);
    TextureManager::Instance()->Load("assets/divider.png", "divider");
    TextureManager::Instance()->Load("assets/ball.png", "ball");
    TextureManager::Instance()->Load("assets/player.png", "player");

    GameObject* object = new GameObject();
    object->Init((1280 - 30) / 2, (720 - 640) / 2, 30, 640, "divider");
    m_objects.push_back(object);

    object = new GameObject();
    object->Init(0, 0, 30, 30, "ball");
    m_objects.push_back(object);

    object = new Player(1);
    object->Init(0, 100, 30, 140, "player");
    m_objects.push_back(object);

    object = new Player(2);
    object->Init(1280-30, 0, 30, 140, "player");
    m_objects.push_back(object);

    return true;
}

void Game::Clean()
{
    for (std::size_t i = 0; i < m_objects.size(); i++)
        m_objects[i]->Clean();
    m_objects.clear();

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
    for (std::size_t i = 0; i < m_objects.size(); i++)
        m_objects[i]->Update();
}

void Game::Render()
{
    SDL_RenderClear(m_pRenderer);

    for (std::size_t i = 0; i < m_objects.size(); i++)
        m_objects[i]->Draw();

    SDL_RenderPresent(m_pRenderer);
}