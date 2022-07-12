#ifndef BALL_H
#define BALL_H

#include "GameObject.h"

class Ball : public GameObject {
    int m_respawned;
    int m_collised;
public:
    Ball() {}

    virtual void Init(int x, int y, int w, int h, int textureID,
                      int callbackID = 0, int animSpeed = 0);
    virtual void Update();

    // Returns who get score: 1 - first player, 2 - second, 0 - none
    int Respawned() { return m_respawned; }
    /*
     * Returns who collised with the ball in current frame:
     * 1 - first, 2 - second, 0 - none
     */
    int Collised() { return m_collised; }
    void CheckCollision(GameObject* pObject);
private:
    void Respawn(int who);
};

#endif
