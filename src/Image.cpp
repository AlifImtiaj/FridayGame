#include "Image.h"

namespace friday {
Image::Image(const std::string &filename) {
    m_filePath = filename;
}

Image::Image(const std::string &filename, glm::vec2 position) {
    m_filePath = filename;
    m_position = position;
}

Image::Image(const std::string &filename, glm::vec2 position, glm::vec2 scale) {
    m_filePath = filename;
    m_position = position;
    m_scale = scale;
}

Image::Image(const std::string &filename, glm::vec2 position, glm::vec2 scale, float rotation) {
    m_filePath = filename;
    m_position = position;
    m_scale = scale;
    m_rotation = rotation;
}

Image::~Image() {
    if (m_texture) SDL_DestroyTexture(m_texture);
}

void Image::CreateTexture(SDL_Renderer* renderer) {
    m_surface = IMG_Load(m_filePath.c_str());

    if (!m_surface) {
        SDL_Log("Failed to load image '%s': %s", m_filePath.c_str(), SDL_GetError());
        return;
    }

    m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);

    if (!m_texture) {
        SDL_Log("Failed to create texture: %s", SDL_GetError());
        SDL_DestroySurface(m_surface);
        m_surface = nullptr;
        return;
    }

    m_imageSize = { static_cast<float>(m_surface->w), static_cast<float>(m_surface->h) };

    SDL_DestroySurface(m_surface);
    m_surface = nullptr;

    UpdateOnDimensionChange();
}

void Image::UpdateOnDimensionChange() {
    m_src = {0, 0, m_imageSize.x, m_imageSize.y};
    m_dst = {m_position.x, m_position.y, m_scale.x * m_imageSize.x, m_scale.y * m_imageSize.y};
}

// getter and setter part
#pragma region -GETTER SETTER-
void Image::SetPosition(glm::vec2 position) {
    m_position = position;
    UpdateOnDimensionChange();
}

void Image::SetPosition(float x, float y) {
    m_position.x = x;
    m_position.y = y;
    UpdateOnDimensionChange();
}
void Image::SetScale(glm::vec2 scale) {
    m_scale = scale;          
    UpdateOnDimensionChange();
}
void Image::SetScale(float x, float y) {
    m_scale.x = x;
    m_scale.y = y;
    UpdateOnDimensionChange();
}
void Image::SetRotation(float rotation) {
    m_rotation = rotation;
    UpdateOnDimensionChange();
}

glm::vec2 Image::GetPosition() {
    return m_position;
}
glm::vec2 Image::GetScale() {
    return m_scale;
}
float Image::GetRotation() {
    return m_rotation;
}
#pragma endregion

void Image::Render(SDL_Renderer *renderer) {
    if (!m_texture || !renderer) return;

    SDL_RenderTextureRotated(renderer, m_texture, &m_src, &m_dst, m_rotation, NULL, SDL_FlipMode::SDL_FLIP_NONE);
    
}


}