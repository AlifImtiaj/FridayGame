#pragma once
#include <SDL3/SDL_render.h>

namespace Friday {
class Level {
protected:
    SDL_Renderer * m_renderer = nullptr;

public:
    void AcquireRenderer(SDL_Renderer * renderer);
    virtual void Start() = 0;
    virtual void Update(const float& deltaTime) = 0;
    virtual void Render() = 0;

private:


};


}