#include "InputHandler.h"

#include "Player.h"

const int PLAYER_SPEED = 10;
const int DECISION_DELAY = 60;
const int MIN_HIT_DELAY = 200;
const int HIT_DELAY_RANGE = 300;
const int MAX_PREDICTION_ITERATIONS = 2;

const int PREDICTION_ERROR_CHANCE = 30;
const int PREDICTION_ERROR_RANGE = 150;

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
        if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_W))
            m_velocity.SetY(-PLAYER_SPEED);
        else if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_S))
            m_velocity.SetY(PLAYER_SPEED);
        else
            m_velocity.SetY(0);
        break;

    case SECOND_PLAYER:
        if (InputHandler::Instance()->IsKeyDown(SDLK_UP))
            m_velocity.SetY(-PLAYER_SPEED);
        else if (InputHandler::Instance()->IsKeyDown(SDLK_DOWN))
            m_velocity.SetY(PLAYER_SPEED);
        else
            m_velocity.SetY(0);
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
        m_bHoldPosition = false;

        m_lastHit = SDL_GetTicks();
        m_hitDelay = MIN_HIT_DELAY + rand() % HIT_DELAY_RANGE;
        return;
    }

    // Decisions
    if (SDL_GetTicks() - m_lastDecision < DECISION_DELAY)
        return;

    m_lastDecision = SDL_GetTicks();

    // Handle hold position param
    if (m_bHoldPosition)
    {
        // If ball just respawned and we still holding the position
        if (m_pBall->GetVelocity().GetX() == Ball::BALL_RESPAWNED_SPEED)
            m_bHoldPosition = false;
        else
            return;
    }

    // Try to take the position on the middle of map
    if (m_pBall->GetVelocity().GetX() <= 0)
    {
        // Already there
        if (720/3 <= m_position.GetY() + m_height/3 &&
            720*2/3 >= m_position.GetY() + m_height*2/3)
            return;

        if (720/2 < m_position.GetY())
            m_velocity.SetY(-PLAYER_SPEED);
        else
            m_velocity.SetY(PLAYER_SPEED);

        return;
    }

    // Try to predict where will be the ball
    int width = m_pBall->GetWidth();
    int height = m_pBall->GetHeight();
    Vector2D position = m_pBall->GetPosition();
    Vector2D velocity = m_pBall->GetVelocity();

    bool bPredicted = false;

    if (static_cast<int>(velocity.GetX()) != 0 ||
        static_cast<int>(velocity.GetY()) != 0)
    {
        for (int i = 0; i < MAX_PREDICTION_ITERATIONS; i++)
        {
            while (position.GetY() > 0 && position.GetY() + height < 720 &&
                   position.GetX() + width < m_position.GetX())
                position += velocity;

            if (position.GetY() < 0)
            {
                velocity.SetY(PLAYER_SPEED);
            }
            else if (position.GetY() + height >= 720)
            {
                velocity.SetY(-PLAYER_SPEED);
            }
            else if (position.GetX() + width >= m_position.GetX())
            {
                bPredicted = true;
                // Even AI can make mistakes...
                if (rand() % 100 < PREDICTION_ERROR_CHANCE)
                {
                    int error = rand() % PREDICTION_ERROR_RANGE;
                    if (rand() % 2)
                        error = -error;

                    position.SetY(position.GetY() + error);
                }

                break;
            }
        }
    }

    // Align to predicted position
    if (bPredicted)
    {
        // Check if we already aligned
        if (position.GetY() + height > m_position.GetY() &&
            position.GetY() < m_position.GetY() + m_height)
        {
            m_bHoldPosition = true;
            m_velocity.SetY(0);
            return;
        }

        // Try to align
        if (position.GetY() < m_position.GetY() + (m_height - height)/2)
            m_velocity.SetY(-PLAYER_SPEED);
        else
            m_velocity.SetY(PLAYER_SPEED);
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
        m_velocity.SetY(-PLAYER_SPEED);
    else
        m_velocity.SetY(PLAYER_SPEED);
}
