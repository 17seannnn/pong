#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>

#include "Object.h"
#include "Vector2D.h"
#include "TextureManager.h"

class GameObject : public Object {
protected:
    Vector2D m_position;
    Vector2D m_velocity;
    int m_width;
    int m_height;
    void (*m_callback)(); // For menu buttons
    int m_currentFrame;
    int m_currentRow;
    int m_numFrames;
    int m_numRows;
    int m_textureID;
public:
    GameObject() : Object() {}

    virtual void Init(int x, int y, int w, int h, int textureID,
                      void (*callback)() = 0);
    virtual void Clean() { delete this; }
    virtual void Update() {}
    virtual void Draw() {
        TextureManager::Instance()->Draw(m_position.GetX(), m_position.GetY(),
                                         m_width, m_height,
                                         m_currentFrame, m_currentRow,
                                         m_textureID);
    }

    Vector2D& GetPosition() { return m_position; }
    Vector2D& GetVelocity() { return m_velocity; }
    int GetWidth() { return m_width; }
    int GetHeight() { return m_height; }
};

#endif
