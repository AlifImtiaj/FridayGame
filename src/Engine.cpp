
#include "Engine.h"

#include <chrono>


Friday::Engine::Engine(const std::string& title, int width, int height)
    : m_windowTitle(title),
    m_windowSize(width, height)
{
}

Friday::Engine::~Engine() {
    if (m_renderer)
        SDL_DestroyRenderer(m_renderer);

    if (m_window)
        SDL_DestroyWindow(m_window);

    if (m_mixer)
        MIX_DestroyMixer(m_mixer);

    MIX_Quit();
    SDL_Quit();
}

bool Friday::Engine::Init() {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("Initialization failed. Error: %s\n", SDL_GetError());
        return false;
    }
    if (!MIX_Init()) {
        SDL_Log("Initialization failed. Error: %s\n", SDL_GetError());
        return false;
    }
    m_window = SDL_CreateWindow(
        m_windowTitle.c_str(),
        static_cast<int>(m_windowSize.x),
        static_cast<int>(m_windowSize.y),
        SDL_WINDOW_RESIZABLE
    );

    if (!m_window) {
        SDL_Log("Window creation failed. Error: %s", SDL_GetError());
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, nullptr);

    if (!m_renderer) {
        SDL_Log("Renderer creation failed. Error: %s", SDL_GetError());
        return false;
    }


    m_mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
    if (!m_mixer) {
        SDL_Log("Mixer Initialization failed. Error: %s\n", SDL_GetError());
        return false;
    }

    m_isGameRunning = true;
    return true;
}

void Friday::Engine::Run() {
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

void Friday::Engine::Tick() {
    HandleInput();
    Update();
    Render();
}

void Friday::Engine::HandleInput() {
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

        switch (event.type) {
            case SDL_EVENT_WINDOW_RESIZED:
                int x, y;
                SDL_GetWindowSize(m_window, &x, &y);
                m_windowSize.x = (float)x;
                m_windowSize.y = (float)y;
                SDL_Log("Resized\n");
                break;
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
            m_targetFPS = 90;
            break;
        case SDL_SCANCODE_4:
            m_isVsyncOn = !m_isVsyncOn;
            SDL_SetRenderVSync(m_renderer, m_isVsyncOn);
            SDL_Log("Vsync: %d\n", m_isVsyncOn);
            break;

        default:
            break;
        }
    }
}

void Friday::Engine::Start() {
    
}

void Friday::Engine::Update() {
    
}

void Friday::Engine::Render() {
    SDL_SetRenderDrawColor(m_renderer, 0,0,0, 255);
    SDL_RenderClear(m_renderer);

    SDL_RenderPresent(m_renderer);
}
