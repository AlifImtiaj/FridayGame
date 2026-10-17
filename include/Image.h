#pragma once
#include <pch.h>

#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_render.h>
#include <glm/vec2.hpp>

namespace friday {
    class Image {
    private:
        SDL_Surface * m_surface = nullptr;
        SDL_Texture * m_texture = nullptr;
    
        glm::vec2 m_position {0,0};
        glm::vec2 m_scale {1,1};
        glm::vec2 m_imageSize {0,0};

        float m_rotation;

        SDL_FRect m_src;
        SDL_FRect m_dst;

        std::string m_filePath;

    public:
        Image(const std::string& filename);
        Image(const std::string& filename, glm::vec2 position);
        Image(const std::string& filename, glm::vec2 position, glm::vec2 scale);
        Image(const std::string& filename, glm::vec2 position, glm::vec2 scale, float rotation);
        ~Image();
        
    private:
        void CreateTexture(SDL_Renderer* renderer);
        
        // getter and setter
        void SetPosition(glm::vec2 position);
        void SetPosition(float x, float y);
        void SetScale(glm::vec2 scale);
        void SetScale(float x, float y);
        void SetRotation(float rotation);

        glm::vec2 GetPosition();
        glm::vec2 GetScale();
        float GetRotation();


        void Render(SDL_Renderer* renderer);

    };
}
