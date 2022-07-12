#include "InputHandler.h"

#include "Player.h"

const int SPEED = 10;

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
    switch (m_who)
    {
    case FIRST_PLAYER:
        if (InputHandler::Instance()->IsKeyDown(SDLK_w))
            m_velocity.SetY(-SPEED);
        else if (InputHandler::Instance()->IsKeyDown(SDLK_s))
            m_velocity.SetY(SPEED);
        else
            m_velocity.SetY(0);
        break;

    case SECOND_PLAYER:
        if (InputHandler::Instance()->IsKeyDown(SDLK_UP))
            m_velocity.SetY(-SPEED);
        else if (InputHandler::Instance()->IsKeyDown(SDLK_DOWN))
            m_velocity.SetY(SPEED);
        else
            m_velocity.SetY(SPEED);
        break;

    case AI_PLAYER:
        HandleAI();
        break;

    default:
        break;
    }
}

void Player::HandleAI()
{
    if (m_pBall->GetPosition().GetY() < m_position.GetY())
        m_velocity.SetY(-SPEED);
    else
        m_velocity.SetY(SPEED);
}
