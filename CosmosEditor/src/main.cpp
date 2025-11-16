#include "core.hpp"
#include "layers/editor_layer.hpp"

int main(int argc, char* argv[])
{
	cosmos::core::ApplicationSpecification appSpecs;
	appSpecs.name = "Cosmos Editor";
	appSpecs.windowSpecs.width = 1280;
	appSpecs.windowSpecs.height = 720;

	cosmos::core::Application app(appSpecs);
	app.PushLayer<cosmos::EditorLayer>();
	app.Run();

	return 0;
}