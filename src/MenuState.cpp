#include "GameObject.h"
#include "TextureManager.h"

#include "MenuState.h"

MenuState::MenuState()
{
    Object* pObject = new GameObject();
    pObject->Init(0, 0, 1280, 720, TEXTURE_MENU_BACKGROUND);
    m_objects.PushBack(pObject);
}

void MenuState::Update()
{
    for (int i = 0; i < m_objects.Size(); i++)
        m_objects[i]->Update();
}

void MenuState::Render()
{
    for (int i = 0; i < m_objects.Size(); i++)
        m_objects[i]->Draw();
}
