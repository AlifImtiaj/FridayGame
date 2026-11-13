#include "Texture2D.h"

namespace Friday {
Texture2D::~Texture2D() {
    if (m_texture) SDL_DestroyTexture(m_texture);
}
void Texture2D::AcquireRenderer(SDL_Renderer *renderer) {
    m_renderer = renderer;
}
bool Texture2D::CreateTextureFromPath(const std::string &filepath) {

    if (m_texture) {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;  
    }
    textureSize = {0,0};

    if (!m_renderer) {
        SDL_Log("No renderer acquired\n");
        return false;
    }

    SDL_Surface * m_surface = IMG_Load(filepath.c_str());

    if (!m_surface) {
        SDL_Log("Failed to load image '%s'. Error: %s", filepath.c_str(), SDL_GetError());
        return false;
    }

    m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);

    if (!m_texture) {
        SDL_Log("Failed to create texture. Error: %s", SDL_GetError());
        SDL_DestroySurface(m_surface);
        return false;
    }

    textureSize = { static_cast<float>(m_surface->w), static_cast<float>(m_surface->h) };

    SDL_DestroySurface(m_surface);
    return true;
}
SDL_Texture *Texture2D::GetTexture() const {
    return m_texture;
}
}