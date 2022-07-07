#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player : public GameObject {
public:
    Player() : GameObject() {}

    virtual void Update();
private:
    void HandleInput();
};

#endif
