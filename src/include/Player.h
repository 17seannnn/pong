#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

enum PlayerType {
    FIRST_PLAYER = 1,
    SECOND_PLAYER,
    AI_PLAYER
};

class Player : public GameObject {
     PlayerType m_who;
public:
    Player(PlayerType who) : GameObject(), m_who(who) {}

    virtual void Update();
private:
    void HandleInput();
};

#endif
