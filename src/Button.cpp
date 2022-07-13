#include "InputHandler.h"

#include "Button.h"

void Button::Update()
{
    int x, y;
    InputHandler::Instance()->GetMousePosition(x, y);

    if (InputHandler::Instance()->IsButtonDown(SDL_BUTTON_LMASK) &&
        y >= m_position.GetY() && y < m_position.GetY() + m_height &&
        x >= m_position.GetX() && x < m_position.GetX() + m_width)
        m_callback();
}
