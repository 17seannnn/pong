#ifndef VECTOR2D
#define VECTOR2D

#include "math.h"

class Vector2D {
    float m_x, m_y;
public:
    Vector2D(float x = 0, float y = 0) : m_x(x), m_y(y) {}
    ~Vector2D() {}

    Vector2D operator+(const Vector2D& v2) const
        { return Vector2D(m_x + v2.m_x, m_y + v2.m_y); }
    Vector2D operator+=(const Vector2D& v2)
        { m_x += v2.m_x; m_y += v2.m_y; return *this; }
    Vector2D operator-(const Vector2D& v2) const
        { return Vector2D(m_x - v2.m_x, m_y - v2.m_y); }
    Vector2D operator-=(const Vector2D& v2)
        { m_x -= v2.m_x; m_y -= v2.m_y; return *this; }
    Vector2D operator*(float scalar) const
        { return Vector2D(m_x * scalar, m_y * scalar); }
    Vector2D operator*=(float scalar)
        { m_x *= scalar; m_y *= scalar; return *this; }
    Vector2D operator/(float scalar) const
        { return Vector2D(m_x / scalar, m_y / scalar); }
    Vector2D operator/=(float scalar)
        { m_x /= scalar; m_y /= scalar; return *this; }

    float GetX() const { return m_x; }
    float GetY() const { return m_y; }
    void SetX(float x) { m_x = x; }
    void SetY(float y) { m_y = y; }
    float Length() const { return sqrt(m_x * m_x + m_y * m_y); }

    void Normalize() {
        float l = Length();
        if (l > 0)
            (*this) *= 1/l;
    }
};

#endif
