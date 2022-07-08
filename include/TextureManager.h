#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <map>
#include <string>
#include <SDL2/SDL.h>

class TextureManager {
    static TextureManager* s_pInstance;

    SDL_Renderer* m_pRenderer;

    std::map<std::string, SDL_Texture*> m_textures;
    std::map<std::string, int> m_texturesCount;
public:
    static TextureManager* Instance();
    void Clean();

    void Load(const char* textureFile, const std::string& id);
    void Unload(const std::string& id);
    void Draw(int x, int y, int w, int h, int frame, int row,
              const std::string& textureID);

    void SetRenderer(SDL_Renderer* pRenderer) { m_pRenderer = pRenderer; }
    void GetNumFramesAndRows(const std::string& textureID,
                             int& numFrames, int& numRows);
private:
    TextureManager() {}
    ~TextureManager() {}
};

#endif
