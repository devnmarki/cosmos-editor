#pragma once

#include "core.hpp"

namespace cosmos
{
	class EditorLayer : public core::Layer
	{
	public:
		void OnAttach() override;
		void OnUpdate(float dt) override;
	};
}