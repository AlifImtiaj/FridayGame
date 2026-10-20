#include "Image.h"

namespace Friday {
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

    if (m_texture) return;

    m_surface = IMG_Load(m_filePath.c_str());

    if (!m_surface) {
        SDL_Log("Failed to load image '%s'. Error: %s", m_filePath.c_str(), SDL_GetError());
        return;
    }

    m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);

    if (!m_texture) {
        SDL_Log("Failed to create texture. Error: %s", SDL_GetError());
        SDL_DestroySurface(m_surface);
        m_surface = nullptr;
        return;
    }

    m_imageSize = { static_cast<float>(m_surface->w), static_cast<float>(m_surface->h) };

    SDL_DestroySurface(m_surface);
    m_surface = nullptr;

    UpdateTransform();
}

void Image::UpdateTransform() {
    m_src = {0, 0, m_imageSize.x, m_imageSize.y};
    m_dst = {m_position.x, m_position.y, m_scale.x * m_imageSize.x, m_scale.y * m_imageSize.y};
}

// setter
void Image::SetPosition(glm::vec2 position) {
    m_position = position;
    UpdateTransform();
}

void Image::SetPosition(float x, float y) {
    m_position.x = x;
    m_position.y = y;
    UpdateTransform();
}
void Image::SetScale(glm::vec2 scale) {
    m_scale = scale;          
    UpdateTransform();
}
void Image::SetScale(float x, float y) {
    m_scale.x = x;
    m_scale.y = y;
    UpdateTransform();
}
void Image::SetRotation(float rotation) {
    m_rotation = rotation;
    UpdateTransform();
}

// Getter
glm::vec2 Image::GetPosition() const{
    return m_position;
}
glm::vec2 Image::GetScale() const{
    return m_scale;
}
float Image::GetRotation() const{
    return m_rotation;
}
glm::vec2 Image::GetImageSize() const{
    return m_imageSize;
}

void Image::Render(SDL_Renderer *renderer) const{
    if (!m_texture || !renderer) return;

    SDL_RenderTextureRotated(renderer, m_texture, &m_src, &m_dst, m_rotation, NULL, SDL_FlipMode::SDL_FLIP_NONE);
    
}

}