#pragma once
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_render.h>
#include <glm/vec2.hpp>

#include "Texture2D.h"

namespace Friday {
    class SpriteRenderer {
    private:
        SDL_Renderer * m_renderer = nullptr;

        Texture2D * m_texture2D = nullptr;
    
        glm::vec2 m_position {0,0};
        glm::vec2 m_scale {1,1};

        float m_rotation = 0.0f;

        SDL_FRect m_src;
        SDL_FRect m_dst;


        bool m_isFlippedHorizontally = false;
        bool m_isFlippedVertically = false;
        SDL_FlipMode m_flipMode = SDL_FlipMode::SDL_FLIP_NONE;

    public:
        SpriteRenderer() = default;
        ~SpriteRenderer() = default;
        
    private:
        void UpdateTransform();
        void SetFlipMode();
    
    public:

        // setter
        void SetTexture2D(Texture2D * texture2D);
        void SetPosition(glm::vec2 position);
        void SetPosition(float x, float y);
        void SetScale(glm::vec2 scale);
        void SetScale(float x, float y);
        void SetRotation(float rotation);

        // getter 
        glm::vec2 GetPosition() const;
        glm::vec2 GetScale() const;
        float GetRotation() const;
        glm::vec2 GetTextureSize() const;

        void FlipHorizontal();
        void FlipVertical();

        void Render(SDL_Renderer* renderer) const;

    };
}
