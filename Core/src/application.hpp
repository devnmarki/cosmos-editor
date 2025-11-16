#pragma once

#include <iostream>
#include <vector>

#include <SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

#include "utils/memory_utils.hpp"
#include "window.hpp"
#include "layer.hpp"

namespace cosmos
{
	namespace core
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
			void Stop();

			template<typename TLayer, typename... Args>
			requires(std::is_base_of_v<Layer, TLayer>)
			void PushLayer(Args&&... args)
			{
				m_LayerStack.push_back(CreateScope<TLayer>(std::forward<Args>(args)...));
			}

			template<typename TLayer>
			TLayer* GetLayer()
			{
				for (const auto& layer : m_LayerStack)
				{
					if (auto casted = dynamic_cast<TLayer*>(layer.get()))
						return casted;
				}

				return nullptr;
			}

			static Application& GetInstance();

			Ref<Window> GetWindow();
			std::vector<Scope<Layer>>& GetLayerStack();

		private:
			ApplicationSpecification m_Specs;

			Ref<Window> m_Window;
			bool m_IsRunning;

			std::vector<Scope<Layer>> m_LayerStack;
		};
	}
}