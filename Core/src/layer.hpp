#pragma once

#include <SDL.h>

#include "utils/memory_utils.hpp"

namespace cosmos
{
	namespace core
	{
		class Layer
		{
		public:
			virtual ~Layer() = default;

			virtual void OnAttach() {}
			virtual void OnUpdate(float dt) {}
			virtual void OnRender() {}
			virtual void OnGuiRender() {}
			virtual void OnEvent(SDL_Event& event) {}

			template<std::derived_from<Layer> T, typename... Args>
			void TransitionTo(Args&&... args)
			{
				QueueTransition(CreateScope<T>(std::forward<Args>(args)...));
			}

		private:
			void QueueTransition(Scope<Layer> toLayer);
		};
	}
}