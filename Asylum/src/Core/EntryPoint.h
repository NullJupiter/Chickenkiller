#pragma once

extern Asylum::Application* Asylum::CreateApplication();

#ifdef AM_PLATFORM_WINDOWS
	#include <Windows.h>

	#ifndef AM_DEBUG
		INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
	#else
		int main()
	#endif
#elif AM_PLATFORM_DARWIN
	int main()
#endif
{
	// create application
	auto app = Asylum::CreateApplication();

	// run the application
	app->Run();

	// delete the application
	delete app;

	return 0;
}
