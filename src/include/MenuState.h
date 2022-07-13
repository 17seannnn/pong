#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "GameState.h"

class MenuState : public GameState {
public:
    MenuState();
    ~MenuState() {}

    virtual void Update();
    virtual void Render();
private:
    // Callback functions
    static void PlayAI();
    static void Play2();
};

#endif
