#pragma once

#include <iostream>

#include <SDL.h>

#include "core.hpp"

namespace cosmos
{
	struct ApplicationSpecification
	{
		std::string name = "Cosmos Level Editor";
		WindowSpecification windowSpecs;
	};

	class Application
	{
	public:
		Application(const ApplicationSpecification& specs = ApplicationSpecification());
		~Application();

		void Run();

		Application& GetInstance();

	private:
		ApplicationSpecification m_Specs;

		Scope<Window> m_Window;
		bool m_IsRunning;
	};
}