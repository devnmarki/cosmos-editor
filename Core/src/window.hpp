#pragma once

#include <iostream>

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
	};
}