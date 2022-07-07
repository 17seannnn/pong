#ifndef BALL_H
#define BALL_H

#include "GameObject.h"

class Ball : public GameObject {
public:
    Ball() {}

    void Update() { m_position += m_velocity; }
};

#endif
