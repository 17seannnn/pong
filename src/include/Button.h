#ifndef BUTTON_H
#define BUTTON_H

#include "GameObject.h"

class Button : public GameObject {
public:
    virtual void Update();
    virtual void Draw() {}
};

#endif
