#pragma once

#include "GameObject.h"
#include "SpriteRenderer.h"

namespace Friday {
class Player : public GameObject {
private:
    SpriteRenderer m_sprite;

public:
    SpriteRenderer &GetSprite();

    void Start() override;
    void Update(const float& deltaTime) override;
    void Render(SDL_Renderer * renderer) override;
    
};

}

