#pragma once
#include <string>

#include <SDL3/SDL.h>
#include <glm/vec2.hpp>
#include <SDL3_mixer/SDL_mixer.h>


namespace Friday {

	class Engine {
	private:
		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;
		MIX_Mixer* m_mixer = nullptr;

		SDL_Event e;

		std::string m_windowTitle;

		glm::vec2 m_windowSize;

		bool m_isGameRunning = false;
		bool m_isVsyncOn = false;

		float m_targetFPS = 60;
		float m_deltaTime = 0;
		

	public:
		Engine(const std::string& title, int width, int height);
		~Engine();

	private:
		void Tick();
		void Start();
		void HandleInput();
		void Update();
		void Render();

	public:
		bool Init();
		void Run();
	};


}
