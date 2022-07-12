#ifndef PLAYER_H
#define PLAYER_H

#include "Ball.h"

enum PlayerType {
    FIRST_PLAYER = 1,
    SECOND_PLAYER,
    AI_PLAYER
};

class Player : public GameObject {
    PlayerType m_who;
    Ball* m_pBall; // Only for AI
public:
    Player(PlayerType who, Ball* pBall)
        : GameObject(), m_who(who), m_pBall(pBall) {}

    virtual void Update();
private:
    void HandleInput();
    void HandleAI();
};

#endif
