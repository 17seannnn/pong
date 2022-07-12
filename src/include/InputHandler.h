#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL2/SDL.h>

class InputHandler {
    static InputHandler* s_pInstance;

    const Uint8* m_keyState;
public:
    static InputHandler* Instance();
    void Clean() { delete this; }

    void Update();
    bool IsKeyDown(SDL_Keycode key);
    bool IsKeyDown(SDL_Scancode code);
private:
    InputHandler() {}
    ~InputHandler() {}
};

#endif
