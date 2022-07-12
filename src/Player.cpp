#include "InputHandler.h"

#include "Player.h"

const int SPEED = 10;
const int DECISION_DELAY = 60;
const int MIN_HIT_DELAY = 200;
const int HIT_DELAY_RANGE = 300;

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
    // If we are stunned after hitting the ball
    if (m_hitDelay > 0 && SDL_GetTicks() - m_lastHit < m_hitDelay)
        return;

    // Check for hitting with the ball
    if (m_pBall->Collised() == 2) // Ball doesn't know about AI_PLAYER
    {
        m_lastHit = SDL_GetTicks();
        m_hitDelay = MIN_HIT_DELAY + rand() % HIT_DELAY_RANGE;
        return;
    }

    // Decisions
    if (SDL_GetTicks() - m_lastDecision >= DECISION_DELAY)
    {
        m_lastDecision = SDL_GetTicks();

        // Try to take the position on the middle of map
        if (m_pBall->GetVelocity().GetX() <= 0)
        {
            // Already there
            if (720/3 <= m_position.GetY() + m_height/3 &&
                720*2/3 >= m_position.GetY() + m_height*2/3)
                return;

            if (720/2 < m_position.GetY())
                m_velocity.SetY(-SPEED);
            else
                m_velocity.SetY(SPEED);

            return;
        }

        // Stop if ball is on our Y position
        if (m_pBall->GetPosition().GetY() +
            m_pBall->GetHeight() > m_position.GetY() + m_height/2.5f &&
            m_pBall->GetPosition().GetY() < m_position.GetY() + m_height*2/2.5f)
        {
            m_velocity.SetY(0);
            return;
        }

        // Try to align
        if (m_pBall->GetPosition().GetY() < m_position.GetY())
            m_velocity.SetY(-SPEED);
        else
            m_velocity.SetY(SPEED);
    }
}
