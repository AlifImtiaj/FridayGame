#include "Player.h"

namespace Friday {
SpriteRenderer &Player::GetSprite() {
    return m_sprite;
}

void Player::Start() {
    // m_size.x = 0.5f; m_size.y = 0.5f;
    m_position.y += 100;
    m_sprite.SetPosition(m_position);
    m_sprite.SetScale(m_size);
}

void Player::Update(const float& deltaTime) {

}

void Player::Render(SDL_Renderer *renderer) {
    m_sprite.Render(renderer);
}
}