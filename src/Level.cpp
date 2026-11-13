#include "Level.h"

namespace Friday {
void Level::AcquireRenderer(SDL_Renderer *renderer) {
    m_renderer = renderer;
}
}