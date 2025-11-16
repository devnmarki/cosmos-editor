#pragma once

#include <iostream>

#include "core.hpp"

namespace cosmos
{
	struct ApplicationSpecification
	{
		std::string name = "Cosmos Level Editor";
	};

	class Application
	{
	public:
		Application(const ApplicationSpecification& specs);
		~Application();

		void Run();

		Application& GetInstance();

	private:
		ApplicationSpecification m_Specs;
	};
}