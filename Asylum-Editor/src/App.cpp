#include "App.h"

#include "EditorLayer.h"

void App::OnStartup()
{
	// set window properties
	mWindow->SetWindowTitle("Chickenkiller");
	mWindow->SetVSync(false);

	// init all layers
	mEditorLayer = new EditorLayer();

	mLayerStack->PushLayer(mEditorLayer);

	// set event callbacks
	Asylum::Input::AddKeyPressedCallback(AM_BIND_FN_1(App::OnKeyPressed));
}

void App::OnShutdown()
{
}

void App::OnUpdate(float dt)
{
}

void App::OnKeyPressed(int keycode)
{
	// toggle fullscreen
	static bool isFullscreen = false;
	if (keycode == AM_KEY_F6)
	{
		if (!isFullscreen)
			mWindow->SetFullscreenMode();
		else
			mWindow->SetWindowedMode(50, 50, 1280, 720);

		isFullscreen = !isFullscreen;
	}
}