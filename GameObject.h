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
    int m_callbackID; // For menu buttons
    int m_animSpeed;  // For animated text
    int m_currentFrame;
    int m_currentRow;
    int m_numFrames;
    int m_numRows;
    std::string m_textureID;
public:
    GameObject() : Object() {}

    virtual void Init(int x, int y, int w, int h, std::string textureID,
                      int callbackID = 0, int animSpeed = 0);
    virtual void Clean() { delete this; }
    virtual void Update() {}
    virtual void Draw() {
        TextureManager::Instance()->Draw(m_position.GetX(), m_position.GetY(),
                                         m_width, m_height,
                                         m_currentFrame, m_currentRow,
                                         m_textureID);
    }
};

#endif
