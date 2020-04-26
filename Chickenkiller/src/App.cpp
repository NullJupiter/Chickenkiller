#include "App.h"

// include all layers
#include "Layers/GameLayer.h"

void App::OnStartup()
{
	// init game layer
	mGameLayer = new GameLayer();

	mLayerStack->PushLayer(mGameLayer);
}

void App::OnShutdown()
{
}

void App::OnUpdate(float dt)
{
	// quit app when escape button is pressed
	if (Asylum::Input::IsKeyPressed(GLFW_KEY_ESCAPE))
		Asylum::Window::Get()->Close();
}
