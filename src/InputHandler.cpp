#include "Game.h"

#include "InputHandler.h"

InputHandler* InputHandler::s_pInstance = 0;

InputHandler* InputHandler::Instance()
{
    if (!s_pInstance)
        s_pInstance = new InputHandler();
    return s_pInstance;
}

void InputHandler::Update()
{
    SDL_Event e;

    m_keyState = SDL_GetKeyboardState(0);
    m_mouseState = SDL_GetMouseState(&m_mouseX, &m_mouseY);

    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_QUIT:
            Game::Instance()->Quit();
            break;

        case SDL_KEYDOWN:
            if (e.key.keysym.sym == SDLK_ESCAPE)
                Game::Instance()->Quit();
            break;

        default:
            break;
        }
    }
}

bool InputHandler::IsKeyDown(SDL_Keycode key)
{
    if (m_keyState)
        return m_keyState[SDL_GetScancodeFromKey(key)];
    return false;
}

bool InputHandler::IsKeyDown(SDL_Scancode code)
{
    if (m_keyState)
        return m_keyState[code];
    return false;
}

void InputHandler::GetMousePosition(int& x, int& y)
{
    x = m_mouseX;
    y = m_mouseY;
}
