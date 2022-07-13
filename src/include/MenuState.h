#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "GameState.h"

class MenuState : public GameState {
public:
    MenuState();
    ~MenuState() {}

    virtual void Update();
    virtual void Render();
};

#endif
