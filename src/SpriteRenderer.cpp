#include "SpriteRenderer.h"

namespace Friday {

void SpriteRenderer::UpdateTransform() {
    m_src = {0, 0, m_texture2D->textureSize.x, m_texture2D->textureSize.y};
    m_dst = {m_position.x, m_position.y, m_scale.x * m_texture2D->textureSize.x, m_scale.y * m_texture2D->textureSize.y};
}

void SpriteRenderer::SetFlipMode() {
    if (m_isFlippedHorizontally && m_isFlippedVertically)
        m_flipMode = SDL_FlipMode::SDL_FLIP_HORIZONTAL_AND_VERTICAL;
    else if (m_isFlippedHorizontally)
        m_flipMode = SDL_FlipMode::SDL_FLIP_HORIZONTAL;
    else if (m_isFlippedVertically)
        m_flipMode = SDL_FlipMode::SDL_FLIP_VERTICAL;
    else
        m_flipMode = SDL_FlipMode::SDL_FLIP_NONE;
}

void SpriteRenderer::SetTexture2D(Texture2D * texture2D) {
    m_texture2D = texture2D;
    UpdateTransform();
}

// setter
void SpriteRenderer::SetPosition(glm::vec2 position) {
    m_position = position;
    UpdateTransform();
}

void SpriteRenderer::SetPosition(float x, float y) {
    m_position.x = x;
    m_position.y = y;
    UpdateTransform();
}
void SpriteRenderer::SetScale(glm::vec2 scale) {
    m_scale = scale;          
    UpdateTransform();
}
void SpriteRenderer::SetScale(float x, float y) {
    m_scale.x = x;
    m_scale.y = y;
    UpdateTransform();
}
void SpriteRenderer::SetRotation(float rotation) {
    m_rotation = rotation;
    UpdateTransform();
}

// Getter
glm::vec2 SpriteRenderer::GetPosition() const{
    return m_position;
}
glm::vec2 SpriteRenderer::GetScale() const{
    return m_scale;
}
float SpriteRenderer::GetRotation() const{
    return m_rotation;
}
glm::vec2 SpriteRenderer::GetTextureSize() const{
    return m_texture2D->textureSize;
}

void SpriteRenderer::FlipHorizontal() {
    m_isFlippedHorizontally = !m_isFlippedHorizontally;
    SetFlipMode();
}

void SpriteRenderer::FlipVertical() {
    m_isFlippedVertically = !m_isFlippedVertically;
    SetFlipMode();
}

void SpriteRenderer::Render(SDL_Renderer *renderer) const {
    if (!m_texture2D || !m_texture2D->GetTexture() || !renderer) return;
    SDL_RenderTextureRotated(renderer, m_texture2D->GetTexture(), &m_src, &m_dst, m_rotation, NULL, m_flipMode);
}

}