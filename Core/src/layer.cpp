#include "layer.hpp"
#include "application.hpp"

namespace cosmos
{
	namespace core
	{
		void Layer::QueueTransition(Scope<Layer> toLayer)
		{
			auto& layerStack = Application::GetInstance().GetLayerStack();
			for (auto& layer : layerStack)
			{
				if (layer.get() == this)
				{
					layer = std::move(toLayer);
					layer->OnAttach();
					return;
				}
			}
		}
	}
}