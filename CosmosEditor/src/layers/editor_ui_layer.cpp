#include "editor_ui_layer.hpp"

#include <imgui.h>

namespace cosmos
{
	void EditorUILayer::OnGuiRender()
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit", "Alt+F4"))
				{
					core::Application::GetInstance().Stop();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::End();
	}
}