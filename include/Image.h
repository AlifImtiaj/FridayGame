#pragma once
#include <pch.h>

#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_render.h>
#include <glm/vec2.hpp>

namespace Friday {
    class Image {
    private:
        SDL_Surface * m_surface = nullptr;
        SDL_Texture * m_texture = nullptr;
    
        glm::vec2 m_position {0,0};
        glm::vec2 m_scale {1,1};
        glm::vec2 m_imageSize {0,0};

        float m_rotation = 0.0f;

        SDL_FRect m_src;
        SDL_FRect m_dst;

        std::string m_filePath;

        bool m_isFlippedHorizontally = false;
        bool m_isFlippedVertically = false;
        SDL_FlipMode m_flipMode = SDL_FlipMode::SDL_FLIP_NONE;

    public:
        Image(const std::string& filename);
        Image(const std::string& filename, glm::vec2 position);
        Image(const std::string& filename, glm::vec2 position, glm::vec2 scale);
        Image(const std::string& filename, glm::vec2 position, glm::vec2 scale, float rotation);
        ~Image();
        
    private:
        void UpdateTransform();
        void SetFlipMode();
    
    public:
        void CreateTexture(SDL_Renderer* renderer);

        // setter
        void SetPosition(glm::vec2 position);
        void SetPosition(float x, float y);
        void SetScale(glm::vec2 scale);
        void SetScale(float x, float y);
        void SetRotation(float rotation);

        // getter 
        glm::vec2 GetPosition() const;
        glm::vec2 GetScale() const;
        float GetRotation() const;
        glm::vec2 GetImageSize() const;

        void FlipHorizontal();
        void FlipVertical();

        void Render(SDL_Renderer* renderer) const;

    };
}
