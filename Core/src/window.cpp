#include "window.hpp"

namespace cosmos
{
	namespace core
	{
		Window::Window(const WindowSpecification & specs)
			: m_Specs(specs), m_Handle(nullptr), m_Renderer(nullptr)
		{
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
			SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
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
			m_Handle = SDL_CreateWindow(m_Specs.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Specs.width, m_Specs.height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
			if (!m_Handle)
			{
				std::cout << "Failed to create SDL Window. Error: " << SDL_GetError() << std::endl;
				return;
			}

			SDL_GLContext gl_context = SDL_GL_CreateContext(m_Handle);
			SDL_GL_MakeCurrent(m_Handle, gl_context);

			m_Renderer = SDL_CreateRenderer(m_Handle, -1, SDL_RENDERER_ACCELERATED);
			if (!m_Renderer)
			{
				std::cout << "Failed to create SDL Renderer. Error: " << SDL_GetError() << std::endl;
				return;
			}
		}

		void Window::Clear(const utils::Color& clearColor)
		{
			SDL_SetRenderDrawColor(m_Renderer, clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		}

		void Window::BeginFrame()
		{
			SDL_RenderClear(m_Renderer);
		}

		void Window::EndFrame()
		{
			SDL_RenderPresent(m_Renderer);
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
}