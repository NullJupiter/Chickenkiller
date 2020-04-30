#include "App.h"

#ifdef AM_PLATFORM_WINDOWS
	#include <Windows.h>

	#ifndef AM_DEBUG
		INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
	#else
		int main()
	#endif
#endif
{
	// create application
	App* app = new App();

	// run the application
	app->Run();
	
	// delete the application
	delete app;

	return 0;
}