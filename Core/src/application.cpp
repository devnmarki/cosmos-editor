#include "application.hpp"

namespace cosmos
{
	namespace core
	{
		static Application* s_Instance = nullptr;

		Application::Application(const ApplicationSpecification& specs)
			: m_Specs(specs), m_IsRunning(true)
		{
			s_Instance = this;

			if (m_Specs.windowSpecs.title.empty())
				m_Specs.windowSpecs.title = m_Specs.name;

			m_Window = CreateRef<Window>(m_Specs.windowSpecs);
			m_Window->Create();
		}

		Application::~Application()
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplSDL2_Shutdown();
			ImGui::DestroyContext();

			SDL_Quit();

			s_Instance = nullptr;
		}

		void Application::Run()
		{
			const int TARGET_FPS = 60;
			const int FRAME_DELAY = 1000 / TARGET_FPS;

			uint32_t frameStart;
			int frameTime;

			uint32_t lastTime = SDL_GetTicks();
			float deltaTime = 0.0f;

			SDL_Event event;

			IMGUI_CHECKVERSION();
			ImGui::CreateContext();

			ImGuiIO& io = ImGui::GetIO(); (void)io;
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

			ImGui::StyleColorsDark();

			ImGuiStyle& style = ImGui::GetStyle();
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
				style.WindowRounding = 0.0f;
				style.Colors[ImGuiCol_WindowBg].w = 1.0f;
			}

			ImGui_ImplSDL2_InitForOpenGL(m_Window->GetHandle(), SDL_GL_GetCurrentContext());
			ImGui_ImplOpenGL3_Init("#version 130");

			while (m_IsRunning)
			{
				frameStart = SDL_GetTicks();

				uint32_t currentTime = SDL_GetTicks();
				deltaTime = (currentTime - lastTime) / 1000.0f;
				lastTime = currentTime;

				if (deltaTime > 0.1f)
					deltaTime = 0.1f;

				while (SDL_PollEvent(&event))
				{
					ImGui_ImplSDL2_ProcessEvent(&event);

					if (event.type == SDL_QUIT)
						m_IsRunning = false;
					if (event.type == SDL_WINDOWEVENT &&
						event.window.event == SDL_WINDOWEVENT_CLOSE &&
						event.window.windowID == SDL_GetWindowID(m_Window->GetHandle()))
						m_IsRunning = false;

					for (const auto& layer : m_LayerStack)
						layer->OnEvent(event);
				}

				ImGui_ImplOpenGL3_NewFrame();
				ImGui_ImplSDL2_NewFrame();
				ImGui::NewFrame();

				ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->WorkPos);
				ImGui::SetNextWindowSize(viewport->WorkSize);
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

				ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
				windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
				windowFlags |= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
				windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
				ImGui::Begin("DockSpace Demo", nullptr, windowFlags);
				ImGui::PopStyleVar();
				ImGui::PopStyleVar(2);

				ImGuiID dockspaceId = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

				for (const auto& layer : m_LayerStack)
					layer->OnGuiRender();

				for (const auto& layer : m_LayerStack)
					layer->OnUpdate(deltaTime);

				m_Window->Clear(utils::Color::WHITE);
				m_Window->BeginFrame();

				for (const auto& layer : m_LayerStack)
					layer->OnRender();

				ImGui::Render();
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

				if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
					SDL_Window* backupCurrentWindow = SDL_GL_GetCurrentWindow();
					SDL_GLContext backupCurrentContext = SDL_GL_GetCurrentContext();
					ImGui::UpdatePlatformWindows();
					ImGui::RenderPlatformWindowsDefault();
					SDL_GL_MakeCurrent(backupCurrentWindow, backupCurrentContext);
				}

				SDL_GL_SwapWindow(m_Window->GetHandle());

				frameTime = SDL_GetTicks() - frameStart;
				if (frameTime < FRAME_DELAY)
				{
					SDL_Delay(FRAME_DELAY - frameTime);
				}
			}
		}

		void Application::Stop()
		{
			m_IsRunning = false;
		}

		Application& Application::GetInstance()
		{
			return *s_Instance;
		}

		Ref<Window> Application::GetWindow()
		{
			return m_Window;
		}

		std::vector<Scope<Layer>>& Application::GetLayerStack()
		{
			return m_LayerStack;
		}
	}
}