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
    for (std::map<std::string, SDL_Texture*>::iterator it = m_textures.begin();
         it != m_textures.end();
         ++it)
        SDL_DestroyTexture(it->second);
    m_textures.clear();
    m_texturesCount.clear();

    delete this;
}

void TextureManager::Load(const char* textureFile, const std::string& id)
{
    if (m_texturesCount.find(id) != m_texturesCount.end())
    {
        m_texturesCount[id]++;
        std::cout << "Already have " << id << " texture\n";
        return;
    }

    SDL_Surface* pTempSurface = IMG_Load(textureFile);
    if (!pTempSurface)
        // We don't return from this function, just output message
        std::cout << "Can't load image " << textureFile << std::endl;

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
    if (!pTexture)
        std::cout << "Can't create texture " << textureFile << std::endl;
    SDL_FreeSurface(pTempSurface);

    m_textures[id] = pTexture;
    m_texturesCount[id] = 1;
}

void TextureManager::Unload(const std::string& id)
{
    // Return if we have more than 1 copy
    if (m_texturesCount[id] > 1)
    {
        m_texturesCount[id]--;
        return;
    }

    SDL_DestroyTexture(m_textures[id]);
    m_textures.erase(id);
    m_texturesCount.erase(id);
}

void TextureManager::Draw(int x, int y, int w, int h, int frame, int row,
                          const std::string& textureID)
{
    SDL_Rect src, dst;

    src.x = frame * w;
    src.y = row * h;
    dst.w = src.w = w;
    dst.h = src.h = h;
    dst.x = x;
    dst.y = y;

    SDL_RenderCopy(m_pRenderer, m_textures[textureID], &src, &dst);
}

void TextureManager::GetNumFramesAndRows(const std::string& textureID,
                                         int& numFrames, int& numRows)
{
    SDL_QueryTexture(m_textures[textureID], 0, 0, &numFrames, &numRows);
}
