#include <iostream>

#include "Ball.h"

const int MAX_SPEED = 20;
const float SPEED_PARTS = 5.0f;
const float SPEED_PART = MAX_SPEED / SPEED_PARTS;

void Ball::Update()
{
    m_position += m_velocity;

    if (m_position.GetY() <= 0 || m_position.GetY() >= 720 - 30)
        m_velocity.SetY(-m_velocity.GetY());
}

void Ball::Respawn()
{
    m_position = Vector2D((1280 - 30) / 2, (720 - 30) / 2);
    if (rand() % 2)
        m_velocity.SetX(-MAX_SPEED/2);
    else
        m_velocity.SetX(MAX_SPEED/2);
    m_velocity.SetY(MAX_SPEED/10 + rand() % (MAX_SPEED/3));
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
            m_velocity.SetX(MAX_SPEED);
        else
            return;
    }
    else
    {
        int checkX = pObject->GetPosition().GetX();
        if (checkX <= m_position.GetX() + m_width &&
            checkX > m_position.GetX() &&
            pObject->GetPosition().GetY() < m_position.GetY() + m_height &&
            pObject->GetPosition().GetY() + pObject->GetHeight() > m_position.GetY())
            m_velocity.SetX(-MAX_SPEED);
        else
            return;
    }

    // If Ball's top is over player's half
    if (m_position.GetY() <= pObject->GetPosition().GetY() + pObject->GetHeight()/2)
        m_velocity.SetY( -SPEED_PART * ( SPEED_PARTS -
        ( ( m_position.GetY() + m_height - pObject->GetPosition().GetY() ) /
        ( 70 / SPEED_PARTS ) ) ) );
    else
        ;

    std::cout << m_velocity.GetY() << std::endl;
}
