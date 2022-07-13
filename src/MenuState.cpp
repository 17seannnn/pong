#include "Game.h"
#include "InputHandler.h"
#include "PlayState.h"
#include "Button.h"

#include "MenuState.h"

MenuState::MenuState()
{
    Object* pObject = new GameObject();
    pObject->Init(0, 0, 1280, 720, TEXTURE_MENU_BACKGROUND);
    m_objects.PushBack(pObject);

    pObject = new Button();
    pObject->Init(230, 300, 380, 120, TEXTURE_NONE, PlayAI);
    m_objects.PushBack(pObject);

    pObject = new Button();
    pObject->Init(650, 300, 380, 120, TEXTURE_NONE, Play2);
    m_objects.PushBack(pObject);
}

void MenuState::Update()
{
    for (int i = 0; i < m_objects.Size(); i++)
        m_objects[i]->Update();

    if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_RETURN))
        Game::Instance()->ChangeState(new PlayState());
}

void MenuState::Render()
{
    for (int i = 0; i < m_objects.Size(); i++)
        m_objects[i]->Draw();
}

void MenuState::PlayAI()
{
    Game::Instance()->ChangeState(new PlayState());
}

void MenuState::Play2()
{
    Game::Instance()->ChangeState(new PlayState());
}
