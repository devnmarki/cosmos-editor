#include "application.hpp"

int main(int argc, char* argv[])
{
	cosmos::ApplicationSpecification appSpecs;
	appSpecs.name = "Cosmos Editor";

	cosmos::Application app(appSpecs);
	app.Run();

	return 0;
}