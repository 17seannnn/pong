#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL2/SDL.h>

#include "Vector.h"

enum {
    TEXTURE_MENU_BACKGROUND = 0,
    TEXTURE_DIVIDER,
    TEXTURE_BALL,
    TEXTURE_PLAYER,
    TEXTURE_NUMBERS
};

class TextureManager {
    static TextureManager* s_pInstance;

    SDL_Renderer* m_pRenderer;
    Vector<SDL_Texture*> m_textures;
public:
    static TextureManager* Instance();
    void Clean();

    void Load(const char* textureFile, int id);
    void Draw(int x, int y, int w, int h, int frame, int row, int id);

    void SetRenderer(SDL_Renderer* pRenderer) { m_pRenderer = pRenderer; }
    void GetNumFramesAndRows(int id, int& numFrames, int& numRows);
private:
    TextureManager() {}
    ~TextureManager() {}
};

#endif
