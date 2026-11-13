#pragma once
#include <SDL3/SDL_render.h>

namespace Friday {
class LevelManager {
private:
    SDL_Renderer * m_renderer = nullptr;

public:
    LevelManager() = default;
    ~LevelManager() = default;
private:

public:
    void AcquireRenderer(SDL_Renderer * renderer);
    void Start();
    void Update(const float& deltaTime);
    void Render();

};
}