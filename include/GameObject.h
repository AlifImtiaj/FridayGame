#pragma once
#include <glm/vec2.hpp>
#include <SDL3/SDL_render.h>

namespace Friday {
class GameObject {
protected:
    glm::vec2 m_position = {0,0};
    glm::vec2 m_size = {1,1};
    float m_rotation = 0;

public:


private:

public:
    virtual void Start() = 0;
    virtual void Update(const float& deltaTime) = 0;
    virtual void Render(SDL_Renderer* renderer) = 0;
};
}
