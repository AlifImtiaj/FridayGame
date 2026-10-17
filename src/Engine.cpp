
#include "Engine.h"

#include <SDL3/SDL.h>
#include <chrono>


friday::Engine::Engine(const std::string& title, int width, int height)
    : m_windowTitle(title),
    m_windowSize(width, height)
{
}

friday::Engine::~Engine() {
    if (m_renderer)
        SDL_DestroyRenderer(m_renderer);

    if (m_window)
        SDL_DestroyWindow(m_window);

    SDL_Quit();
}

bool friday::Engine::Init() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return false;
    }
    m_window = SDL_CreateWindow(
        m_windowTitle.c_str(),
        static_cast<int>(m_windowSize.x),
        static_cast<int>(m_windowSize.y),
        SDL_WINDOW_RESIZABLE
    );

    if (!m_window) {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, nullptr);

    if (!m_renderer) {
        SDL_Log("Renderer creation failed: %s", SDL_GetError());
        return false;
    }

    m_isGameRunning = true;
    return true;
}

void friday::Engine::HandleInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            m_isGameRunning = false;
            continue;
        }

        if (event.type != SDL_EVENT_KEY_DOWN ||
            event.key.repeat) {
            continue;
        }

        switch (event.key.scancode) {
        case SDL_SCANCODE_0:
            m_targetFPS = 0; // uncapped fps
            break;
        case SDL_SCANCODE_1:
            m_targetFPS = 60;
            break;
        case SDL_SCANCODE_2:
            m_targetFPS = 75;
            break;
        case SDL_SCANCODE_3:
            m_targetFPS = 10;
            break;
        case SDL_SCANCODE_4:
            m_isVsyncOn = !m_isVsyncOn;
            SDL_SetRenderVSync(m_renderer, m_isVsyncOn);
            break;
        default:
            break;
        }
    }
}

void friday::Engine::Tick() {
    HandleInput();
    Update();
    Render();
}


void friday::Engine::Run() {

    Start();
    using clock = std::chrono::steady_clock;

    auto previousStart = clock::now();
    auto nextFrame = previousStart;

    while (m_isGameRunning) {
        const auto frameStart = clock::now();

        m_deltaTime = std::min(
            std::chrono::duration<float>(frameStart - previousStart).count(),
            0.1f);
        previousStart = frameStart;

        Tick();

        if (m_isVsyncOn)
            continue;

        if (m_targetFPS > 0) {
            nextFrame += std::chrono::duration_cast<clock::duration>(
                std::chrono::duration<double>(1.0 / m_targetFPS)
            );

            const auto now = clock::now();
            if (nextFrame > now) {
                SDL_DelayPrecise(static_cast<Uint64>(
                    std::chrono::duration_cast<std::chrono::nanoseconds>(
                        nextFrame - now).count()));
            }
            else {
                nextFrame = now; 
            }
        }
        else {
            nextFrame = clock::now(); // this is for uncapped fps
        }
    }
}

void friday::Engine::Start() {
}

void friday::Engine::Update() {

}

void friday::Engine::Render() {
    SDL_SetRenderDrawColor(m_renderer, 20, 10, 30, 255);
    SDL_RenderClear(m_renderer);

    SDL_RenderPresent(m_renderer);
}
