#include "application.hpp"

namespace cosmos
{
	static Application* s_Instance = nullptr;

	Application::Application(const ApplicationSpecification& specs)
		: m_Specs(specs)
	{
		s_Instance = this;
	}

	Application::~Application()
	{
		s_Instance = nullptr;
	}

	void Application::Run()
	{
		std::cout << "Application is running!" << std::endl;
	}

	Application& Application::GetInstance()
	{
		return *s_Instance;
	}
}