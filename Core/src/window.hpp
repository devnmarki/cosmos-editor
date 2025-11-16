#pragma once

#include <iostream>

#include <SDL.h>

namespace cosmos
{
	struct WindowSpecification
	{
		std::string title;
		uint32_t width;
		uint32_t height;
	};

	class Window
	{
	public:
		Window(const WindowSpecification& specs);

		void Create();
		
	private:
		WindowSpecification m_Specs;

		SDL_Window* m_Handle;
		SDL_Renderer* m_Renderer;
	};
}