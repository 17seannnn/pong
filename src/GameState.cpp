#include "GameState.h"

GameState::~GameState()
{
    for (int i = 0; i < m_objects.Size(); i++)
        m_objects[i]->Clean();
    m_objects.Clear();
}
