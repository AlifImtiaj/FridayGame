#include "LevelManager.h"

#include "Level1.h"



namespace Friday {

Level1 lv1;

void LevelManager::AcquireRenderer(SDL_Renderer *renderer) {
    if (!renderer) {
        return;
    }
    m_renderer = renderer;
    lv1.AcquireRenderer(renderer);
}

void LevelManager::Start() {
    lv1.Start();
}

void LevelManager::Update(const float &deltaTime) {
    lv1.Update(deltaTime);
}

void LevelManager::Render() {
    lv1.Render();
}
}
