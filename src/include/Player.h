#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player : public GameObject {
    int m_who;
public:
    Player(int who) : GameObject(), m_who(who) {}

    virtual void Update();
private:
    void HandleInput();
};

#endif
