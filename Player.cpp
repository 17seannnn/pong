#include "InputHandler.h"

#include "Player.h"

void Player::Update()
{
    HandleInput();

    m_position += m_velocity;

    if (m_position.GetY() < 0)
        m_position.SetY(0);
    else if (m_position.GetY() > (720-m_height))
        m_position.SetY(720-m_height);
}

void Player::HandleInput()
{
    if (InputHandler::Instance()->IsKeyDown(SDLK_UP))
        m_velocity.SetY(-10);
    else if (InputHandler::Instance()->IsKeyDown(SDLK_DOWN))
        m_velocity.SetY(10);
    else
        m_velocity.SetY(0);
}
