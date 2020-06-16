#include <Asylum.h>
#include <Core/EntryPoint.h>

#include "Layers/GameLayer.h"

class Chickenkiller : public Asylum::Application
{
private:
	Asylum::Layer* mGameLayer;
public:
	Chickenkiller() : Asylum::Application("Chickenkiller") { OnStartup(); };
	~Chickenkiller() { OnShutdown(); };

	virtual void OnStartup() override
	{
		// set window properties
		mWindow->SetVSync(false);

		// init all layers
		mGameLayer = new GameLayer();

		mLayerStack->PushLayer(mGameLayer);

		// set event callbacks
		Asylum::Input::AddKeyPressedCallback(AM_BIND_FN_1(Chickenkiller::OnKeyPressed));
	}

	virtual void OnShutdown() override
	{

	}

	virtual void OnUpdate(float dt) override
	{

	}
private:
	void OnKeyPressed(int keycode)
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
};

Asylum::Application* Asylum::CreateApplication()
{
	return new Chickenkiller();
}