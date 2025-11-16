#include "window.hpp"

namespace cosmos
{
	Window::Window(const WindowSpecification& specs)
		: m_Specs(specs), m_Handle(nullptr), m_Renderer(nullptr)
	{

	}

	Window::~Window()
	{
		if (m_Renderer)
			SDL_DestroyRenderer(m_Renderer);

		if (m_Handle)
			SDL_DestroyWindow(m_Handle);
	}

	void Window::Create()
	{
		m_Handle = SDL_CreateWindow(m_Specs.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Specs.width, m_Specs.height, SDL_WINDOW_SHOWN);
		if (!m_Handle)
		{
			std::cout << "Failed to create SDL Window. Error: " << SDL_GetError() << std::endl;
			return;
		}

		m_Renderer = SDL_CreateRenderer(m_Handle, -1, SDL_RENDERER_ACCELERATED);
		if (!m_Renderer)
		{
			std::cout << "Failed to create SDL Renderer. Error: " << SDL_GetError() << std::endl;
			return;
		}
	}

	SDL_Window* Window::GetHandle() const
	{
		return m_Handle;
	}

	SDL_Renderer* Window::GetRenderer() const
	{
		return m_Renderer;
	}
}