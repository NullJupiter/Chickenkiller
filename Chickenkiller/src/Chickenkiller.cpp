#include "Application.h"

int main() 
{
	// get the application
	Application* app = Application::Get();

	// initialize the application
	app->Init();

	// run the application
	app->Run();

	// shut down the application
	app->Shutdown();

	return 0;
}