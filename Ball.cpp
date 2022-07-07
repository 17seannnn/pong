#include "Ball.h"

void Ball::Update()
{
    m_position += m_velocity;

    if (m_position.GetY() < 0 || m_position.GetY() > 720-30)
        m_velocity.SetY(-m_velocity.GetY());

    if (m_position.GetX() < 0 || m_position.GetX() > 1280-30)
        m_velocity.SetX(-m_velocity.GetX());
}

void Ball::Respawn()
{
    m_position = Vector2D((1280 - 30) / 2, (720 - 30) / 2);
    if (rand() % 2)
        m_velocity.SetX(-10);
    else
        m_velocity.SetX(10);
    m_velocity.SetY(5);
}
