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

    // AI section
    Ball* m_pBall;
    unsigned m_lastDecision;
public:
    Player(PlayerType who, Ball* pBall)
        : GameObject(), m_who(who), m_pBall(pBall), m_lastDecision(0) {}

    virtual void Update();
private:
    void HandleInput();
    void HandleAI();
};

#endif
