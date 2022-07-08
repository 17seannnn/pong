#ifndef BALL_H
#define BALL_H

#include "GameObject.h"

class Ball : public GameObject {
public:
    Ball() {}

    virtual void Update();

    void Respawn();
    void CheckCollision(GameObject* pObject);
};

#endif
