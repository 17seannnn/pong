#include "Ball.h"

const int MAX_SPEED = 25;

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
        m_velocity.SetX(-10);
    else
        m_velocity.SetX(10);
    m_velocity.SetY(3);
}

void Ball::CheckCollision(GameObject* pObject)
{
    // If x velocity < 0 then we check first player else second
    if (m_velocity.GetX() < 0)
    {
        int check_x = pObject->GetPosition().GetX() + pObject->GetWidth();
        if (check_x >= m_position.GetX() &&
            check_x < m_position.GetX() + m_width &&
            pObject->GetPosition().GetY() < m_position.GetY() + m_height &&
            pObject->GetPosition().GetY() + pObject->GetHeight() > m_position.GetY())
            m_velocity.SetX(-m_velocity.GetX());
    }
    else
    {
        int check_x = pObject->GetPosition().GetX();
        if (check_x <= m_position.GetX() + m_width &&
            check_x > m_position.GetX() &&
            pObject->GetPosition().GetY() < m_position.GetY() + m_height &&
            pObject->GetPosition().GetY() + pObject->GetHeight() > m_position.GetY())
            m_velocity.SetX(-m_velocity.GetX());
    }
}
