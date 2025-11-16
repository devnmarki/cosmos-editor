#include "application.hpp"

namespace cosmos
{
	namespace core
	{
		static Application* s_Instance = nullptr;

		Application::Application(const ApplicationSpecification& specs)
			: m_Specs(specs), m_IsRunning(true)
		{
			s_Instance = this;

			if (m_Specs.windowSpecs.title.empty())
				m_Specs.windowSpecs.title = m_Specs.name;

			m_Window = CreateRef<Window>(m_Specs.windowSpecs);
			m_Window->Create();
		}

		Application::~Application()
		{
			s_Instance = nullptr;
		}

		void Application::Run()
		{
			const int TARGET_FPS = 60;
			const int FRAME_DELAY = 1000 / TARGET_FPS;

			uint32_t frameStart;
			int frameTime;

			uint32_t lastTime = SDL_GetTicks();
			float deltaTime = 0.0f;

			SDL_Event event;
			
			while (m_IsRunning)
			{
				frameStart = SDL_GetTicks();

				uint32_t currentTime = SDL_GetTicks();
				deltaTime = (currentTime - lastTime) / 1000.0f;
				lastTime = currentTime;

				if (deltaTime > 0.1f)
					deltaTime = 0.1f;

				while (SDL_PollEvent(&event))
				{
					if (event.type == SDL_QUIT)
					{
						m_IsRunning = false;
					}

					for (const auto& layer : m_LayerStack)
						layer->OnEvent(event);
				}

				for (const auto& layer : m_LayerStack)
					layer->OnUpdate(deltaTime);

				m_Window->Clear(utils::Color::WHITE);
				m_Window->BeginFrame();
				
				for (const auto& layer : m_LayerStack)
					layer->OnRender();
				
				m_Window->EndFrame();

				frameTime = SDL_GetTicks() - frameStart;
				if (frameTime < FRAME_DELAY)
				{
					SDL_Delay(FRAME_DELAY - frameTime);
				}
			}
		}

		Application& Application::GetInstance()
		{
			return *s_Instance;
		}

		Ref<Window> Application::GetWindow()
		{
			return m_Window;
		}

		std::vector<Scope<Layer>>& Application::GetLayerStack()
		{
			return m_LayerStack;
		}
	}
}