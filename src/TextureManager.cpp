#include <iostream>
#include <SDL2/SDL_image.h>

#include "TextureManager.h"

TextureManager* TextureManager::s_pInstance = 0;

TextureManager* TextureManager::Instance()
{
    if (!s_pInstance)
        s_pInstance = new TextureManager;
    return s_pInstance;
}

void TextureManager::Clean()
{
    for (int i = 0; i < m_textures.Size(); i++)
        SDL_DestroyTexture(m_textures[i]);
    m_textures.Clear();

    delete this;
}

void TextureManager::Load(const char* textureFile, int id)
{
    SDL_Surface* pTempSurface = IMG_Load(textureFile);
    if (!pTempSurface)
        // We don't return from this function, just output message
        std::cout << "Can't load image " << textureFile << std::endl;

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
    if (!pTexture)
        std::cout << "Can't create texture " << textureFile << std::endl;
    SDL_FreeSurface(pTempSurface);

    m_textures[id] = pTexture;
}

void TextureManager::Draw(int x, int y, int w, int h, int frame, int row, int id)
{
    SDL_Rect src, dst;

    src.x = frame * w;
    src.y = row * h;
    dst.w = src.w = w;
    dst.h = src.h = h;
    dst.x = x;
    dst.y = y;

    SDL_RenderCopy(m_pRenderer, m_textures[id], &src, &dst);
}

void TextureManager::GetNumFramesAndRows(int id, int& numFrames, int& numRows)
{
    SDL_QueryTexture(m_textures[id], 0, 0, &numFrames, &numRows);
}
