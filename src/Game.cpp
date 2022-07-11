#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "TextureManager.h"
#include "InputHandler.h"

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

    Object* pObject = new GameObject();
    pObject->Init((1280 - 30) / 2, (720 - 640) / 2, 30, 640, TEXTURE_DIVIDER);
    m_objects.PushBack(pObject);

    m_pBall = new Ball();
    m_pBall->Init(0, 0, 30, 30, TEXTURE_BALL);
    m_objects.PushBack(m_pBall);

    m_pPlayer1 = new Player(1);
    m_pPlayer1->Init(0, (720 - 140) / 2, 30, 140, TEXTURE_PLAYER);
    m_objects.PushBack(m_pPlayer1);

    m_pPlayer2 = new Player(2);
    m_pPlayer2->Init(1280-30, (720 - 140) / 2, 30, 140, TEXTURE_PLAYER);
    m_objects.PushBack(m_pPlayer2);

    m_score1 = 0;
    m_score2 = 0;

    m_bRunning = true;

    return true;
}

void Game::Clean()
{
    for (int i = 0; i < m_objects.Size(); i++)
        m_objects[i]->Clean();
    m_objects.Clear();

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
    for (int i = 0; i < m_objects.Size(); i++)
        m_objects[i]->Update();

    m_pBall->CheckCollision(m_pPlayer1);
    m_pBall->CheckCollision(m_pPlayer2);

    int who = m_pBall->Respawned();
    if (who)
    {
        if (who == 1)
            m_score1++;
        else
            m_score2++;
    }
}

void Game::Render()
{
    SDL_RenderClear(m_pRenderer);

    DrawScores();

    for (int i = 0; i < m_objects.Size(); i++)
        m_objects[i]->Draw();

    SDL_RenderPresent(m_pRenderer);
}

void Game::DrawScores()
{
    // Draw first player's score
    int tempScore = m_score1;
    int i = 0;
    do {
        int n = tempScore % 10;
        tempScore /= 10;
        TextureManager::Instance()->Draw((1280 - 30)/2 - 150 - 80*i, 0,
                                          100, 140, n > 0 ? n-1 : 9, 0,
                                          TEXTURE_NUMBERS);
        i++;
    } while (tempScore > 0);

    // Get count of numbers of second player's score
    tempScore = m_score2;
    i = 0;
    do {
        tempScore /= 10;
        i++;
    } while (tempScore > 0);

    // Draw second player's score
    tempScore = m_score2;
    do {
        int n = tempScore % 10;
        tempScore /= 10;
        TextureManager::Instance()->Draw((1280 - 30)/2 + 80*i, 0,
                                          100, 140, n > 0 ? n-1 : 9, 0,
                                          TEXTURE_NUMBERS);
        i--;
    } while (tempScore > 0);
}
