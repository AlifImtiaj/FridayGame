#include "Level1.h"

#include "Texture2D.h"
#include "Player.h"

namespace Friday {
Texture2D playerTexture;
Player player1;

void Level1::Start() {
    playerTexture.AcquireRenderer(m_renderer);
    playerTexture.CreateTextureFromPath("resource/dvd.png");

    player1.GetSprite().SetTexture2D(&playerTexture);
    player1.Start();
}

void Level1::Update(const float& deltaTime) {
    player1.Update(deltaTime);
}

void Level1::Render() {
    player1.Render(m_renderer);
}
}