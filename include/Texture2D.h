#pragma once

#include <string>
#include <glm/vec2.hpp>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>

namespace Friday {
class Texture2D {
private:
    SDL_Renderer * m_renderer = nullptr;
    SDL_Texture * m_texture = nullptr;
    
public:
    glm::vec2 textureSize {0,0};

    Texture2D() = default;
    ~Texture2D();
    
    private:
    
public:
    void AcquireRenderer(SDL_Renderer* renderer);
    bool CreateTextureFromPath(const std::string& filepath);

    SDL_Texture * GetTexture() const;

};
}