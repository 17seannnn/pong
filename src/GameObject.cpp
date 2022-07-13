#include "GameObject.h"

void GameObject::Init(int x, int y, int w, int h, int textureID,
                      void (*callback)())
{
    m_position = Vector2D(x, y);
    m_velocity = Vector2D(0, 0);
    m_width = w;
    m_height = h;
    m_callback = callback;
    m_currentFrame = 0;
    m_currentRow = 0;
    m_textureID = textureID;

    TextureManager::Instance()->GetNumFramesAndRows(m_textureID, m_numFrames, m_numRows);
}
