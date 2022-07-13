#include "PlayState.h"

PlayState::PlayState(bool AI)
{
    Object* pObject = new GameObject();
    pObject->Init((1280 - 30) / 2, (720 - 640) / 2, 30, 640, TEXTURE_DIVIDER);
    m_objects.PushBack(pObject);

    m_pBall = new Ball();
    m_pBall->Init(0, 0, 30, 30, TEXTURE_BALL);
    m_objects.PushBack(m_pBall);

    m_pPlayer1 = new Player(FIRST_PLAYER, 0);
    m_pPlayer1->Init(0, (720 - 140) / 2, 30, 140, TEXTURE_PLAYER);
    m_objects.PushBack(m_pPlayer1);

    m_pPlayer2 = new Player(AI ? AI_PLAYER : SECOND_PLAYER, m_pBall);
    m_pPlayer2->Init(1280-30, (720 - 140) / 2, 30, 140, TEXTURE_PLAYER);
    m_objects.PushBack(m_pPlayer2);

    m_score1 = 0;
    m_score2 = 0;
}

void PlayState::Update()
{
    for (int i = 0; i < m_objects.Size(); i++)
        m_objects[i]->Update();

    m_pBall->CheckCollision(m_pPlayer1);
    m_pBall->CheckCollision(m_pPlayer2);

    int who = m_pBall->Respawned();
    if (who)
    {
        if (who == FIRST_PLAYER)
            m_score1++;
        else
            m_score2++;
    }
}

void PlayState::Render()
{
    DrawScores();

    for (int i = 0; i < m_objects.Size(); i++)
        m_objects[i]->Draw();
}

void PlayState::DrawScores()
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
