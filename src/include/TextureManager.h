#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>
#include <SDL2/SDL.h>

#include "Vector.h"

const int TEXTURE_DIVIDER = 0;
const int TEXTURE_BALL    = 1;
const int TEXTURE_PLAYER  = 2;
const int TEXTURE_NUMBERS = 3;

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
