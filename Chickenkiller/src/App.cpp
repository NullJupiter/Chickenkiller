#include "App.h"

// include all layers
#include "Layers/GameLayer.h"

void App::OnStartup()
{
	// set window properties
	mWindow->SetWindowTitle("Chickenkiller");
	mWindow->SetVSync(false);

	// init game layer
	mGameLayer = new GameLayer();

	mLayerStack->PushLayer(mGameLayer);

	// toggle fullscreen
	Asylum::Input::AddKeyPressedCallback([this](int keycode)
		{
			static bool isFullscreen = false;
			if (keycode == AM_KEY_F6)
			{
				if (!isFullscreen)
					mWindow->SetFullscreenMode();
				else
					mWindow->SetWindowedMode(50, 50, 1280, 720);

				isFullscreen = !isFullscreen;
			}
		});
}

void App::OnShutdown()
{
}

void App::OnUpdate(float dt)
{
	// quit app when escape button is pressed
	if (Asylum::Input::IsKeyPressed(AM_KEY_ESCAPE))
		Asylum::Window::Get()->Close();
}
