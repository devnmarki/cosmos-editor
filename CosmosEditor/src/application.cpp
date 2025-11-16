#include "application.hpp"

namespace cosmos
{
	static Application* s_Instance = nullptr;

	Application::Application(const ApplicationSpecification& specs)
		: m_Specs(specs), m_IsRunning(true)
	{
		s_Instance = this;

		if (m_Specs.windowSpecs.title.empty())
			m_Specs.windowSpecs.title = m_Specs.name;

		m_Window = CreateScope<Window>(m_Specs.windowSpecs);
		m_Window->Create();
	}

	Application::~Application()
	{
		s_Instance = nullptr;
	}

	void Application::Run()
	{
		while (m_IsRunning)
		{
			SDL_Event event;

			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					m_IsRunning = false;
				}
			}

			// Rendering and update logic would go here
		}
	}

	Application& Application::GetInstance()
	{
		return *s_Instance;
	}
}