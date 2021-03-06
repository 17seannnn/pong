#include "Ball.h"

const float SPEED_PARTS = 5.0f;
const float SPEED_PART = Ball::BALL_MAX_SPEED / SPEED_PARTS;

// There should be constant instead of 70 but...
const float PLAYER_PART = 70 / SPEED_PARTS;

void Ball::Init(int x, int y, int w, int h, int textureID,
                int callbackID)
{
    GameObject::Init(x, y, w, h, textureID);

    Respawn(0);
}

void Ball::Update()
{
    if (m_respawned > 0)
        m_respawned = 0;

    m_position += m_velocity;

    if (m_position.GetY() < 0)
    {
        m_position.SetY(0);
        m_velocity.SetY(-m_velocity.GetY());
    }

    if (m_position.GetY() > 720-30)
    {
        m_position.SetY(720-30);
        m_velocity.SetY(-m_velocity.GetY());
    }

    // Score for second player
    if (m_position.GetX() < -100)
        Respawn(2);
    // Score for first player
    if (m_position.GetX() > 1280+100)
        Respawn(1);
}

void Ball::Respawn(int who)
{
    m_position = Vector2D((1280 - 30) / 2, (720 - 30) / 2);
    // If first player won last round, give ball to the second player
    if (who == 1)
        m_velocity.SetX(Ball::BALL_RESPAWNED_SPEED);
    else
        m_velocity.SetX(-Ball::BALL_RESPAWNED_SPEED);
    m_velocity.SetY(Ball::BALL_MAX_SPEED/10 + rand() %
                    (Ball::BALL_MAX_SPEED/3) * ((rand() % 2) * -1));

    m_respawned = who;
}

void Ball::CheckCollision(GameObject* pObject)
{
    // If x velocity < 0 then we check first player else second
    if (m_velocity.GetX() < 0)
    {
        int checkX = pObject->GetPosition().GetX() + pObject->GetWidth();
        if (checkX >= m_position.GetX() &&
            checkX < m_position.GetX() + m_width &&
            pObject->GetPosition().GetY() < m_position.GetY() + m_height &&
            pObject->GetPosition().GetY() + pObject->GetHeight() > m_position.GetY())
        {
            m_velocity.SetX(Ball::BALL_MAX_SPEED);
            m_collised = 1;
        }
        else
        {
            m_collised = 0;
            return;
        }
    }
    else
    {
        int checkX = pObject->GetPosition().GetX();
        if (checkX <= m_position.GetX() + m_width &&
            checkX > m_position.GetX() &&
            pObject->GetPosition().GetY() < m_position.GetY() + m_height &&
            pObject->GetPosition().GetY() + pObject->GetHeight() > m_position.GetY())
        {
            m_velocity.SetX(-Ball::BALL_MAX_SPEED);
            m_collised = 2;
        }
        else
        {
            m_collised = 0;
            return;
        }
    }

    // If Ball's bottom is over player's half
    float ballBottom = m_position.GetY() + m_height;
    if (ballBottom <= pObject->GetPosition().GetY() + pObject->GetHeight()/2)
    {
        float ballDepth = (ballBottom - pObject->GetPosition().GetY()) / PLAYER_PART;
        if (ballDepth < 0)
            ballDepth = -ballDepth;
        m_velocity.SetY(-SPEED_PART * (SPEED_PARTS - ballDepth));
    }
    else
    {
        float playerHalf = pObject->GetPosition().GetY() + pObject->GetHeight()/2;
        float playerDepth = (m_position.GetY() - playerHalf) / PLAYER_PART;
        if (playerDepth < 0)
            playerDepth = -playerDepth;
        m_velocity.SetY(SPEED_PART * playerDepth);
    }
}
