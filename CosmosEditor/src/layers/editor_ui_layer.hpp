#pragma once

#include "core.hpp"

namespace cosmos
{
	class EditorUILayer : public core::Layer
	{
	public:
		void OnGuiRender() override;
	};
}