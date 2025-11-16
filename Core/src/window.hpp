#pragma once

#include <iostream>

#include <SDL.h>

#include "utils/utils.hpp"

namespace cosmos
{
	namespace core
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
			~Window();

			void Create();

			void Clear(const utils::Color& clearColor);
			void BeginFrame();
			void EndFrame();

			SDL_Window* GetHandle() const;
			SDL_Renderer* GetRenderer() const;

		private:
			WindowSpecification m_Specs;

			SDL_Window* m_Handle;
			SDL_Renderer* m_Renderer;
		};
	}
}