#include "App.h"

int main() 
{
	// create application
	App* app = new App();

	// run the application
	app->Run();

	// delete the application
	delete app;

	return 0;
}