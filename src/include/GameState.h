#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Vector.h"
#include "Object.h"

class GameState {
protected:
    Vector<Object*> m_objects;
public:
    GameState() {}
    virtual ~GameState();

    virtual void Update() = 0;
    virtual void Render() = 0;
};

#endif
