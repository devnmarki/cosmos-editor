#include "application.hpp"

int main(int argc, char* argv[])
{
	cosmos::ApplicationSpecification appSpecs;
	appSpecs.name = "Cosmos Editor";
	appSpecs.windowSpecs.width = 1280;
	appSpecs.windowSpecs.height = 720;

	cosmos::Application app(appSpecs);
	app.Run();

	return 0;
}