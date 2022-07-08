#include "Ball.h"

const int MAX_SPEED = 20;
const float SPEED_PARTS = 5.0f;
const float SPEED_PART = MAX_SPEED / SPEED_PARTS;

// There should be constant instead of 70 but...
const float PLAYER_PART = 70 / SPEED_PARTS;

void Ball::Init(int x, int y, int w, int h, int textureID,
                int callbackID, int animSpeed)
{
    GameObject::Init(x, y, w, h, textureID);

    Respawn(0);
}

void Ball::Update()
{
    if (m_respawned > 0)
        m_respawned = 0;

    m_position += m_velocity;

    if (m_position.GetY() < 0 || m_position.GetY() > 720-30)
        m_velocity.SetY(-m_velocity.GetY());

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
        m_velocity.SetX(MAX_SPEED/2);
    else
        m_velocity.SetX(-MAX_SPEED/2);
    m_velocity.SetY(MAX_SPEED/10 + rand() % (MAX_SPEED/3) * ((rand() % 2) * -1));

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
            m_velocity.SetX(MAX_SPEED);
        }
        else
        {
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
            m_velocity.SetX(-MAX_SPEED);
        }
        else
        {
            return;
        }
    }

    // If Ball's top is over player's half
    if (m_position.GetY() <= pObject->GetPosition().GetY() + pObject->GetHeight()/2)
    {
        float ballBottom = m_position.GetY() + m_height;
        float ballDepth = (ballBottom - pObject->GetPosition().GetY()) / PLAYER_PART;
        m_velocity.SetY(-SPEED_PART * (SPEED_PARTS - ballDepth));
    }
    else
    {
        float playerHalf = pObject->GetPosition().GetY() + pObject->GetHeight()/2;
        float playerDepth = (playerHalf - m_position.GetY()) / PLAYER_PART;
        m_velocity.SetY(SPEED_PART * playerDepth);
    }
}
