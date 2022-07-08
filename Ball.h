#ifndef BALL_H
#define BALL_H

#include "GameObject.h"

class Ball : public GameObject {
    int m_respawned;
public:
    Ball() {}

    virtual void Init(int x, int y, int w, int h, std::string textureID,
                      int callbackID = 0, int animSpeed = 0);
    virtual void Update();

    // Returns: 0 - if no respawned, 1 - score for 1 player, 2 - score for 2
    int Respawned() { return m_respawned; }
    void CheckCollision(GameObject* pObject);
private:
    void Respawn(int who);
};

#endif
