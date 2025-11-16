#include "application.hpp"

int main()
{
	cosmos::ApplicationSpecification appSpecs;
	appSpecs.name = "Cosmos Editor";

	cosmos::Application app(appSpecs);
	app.Run();

	return 0;
}