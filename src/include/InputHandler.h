#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL2/SDL.h>

class InputHandler {
    static InputHandler* s_pInstance;

    const Uint8* m_keyState;
    int m_mouseX, m_mouseY;
    Uint32 m_mouseState;
public:
    static InputHandler* Instance();
    void Clean() { delete this; }

    void Update();
    bool IsKeyDown(SDL_Keycode key);
    bool IsKeyDown(SDL_Scancode code);
    void GetMousePosition(int& x, int& y);
    bool IsButtonDown(Uint32 buttonMask) { return m_mouseState & buttonMask; }
private:
    InputHandler() {}
    ~InputHandler() {}
};

#endif
