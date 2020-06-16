#include <Asylum.h>
#include <Core/EntryPoint.h>

#include "Layers/EditorLayer.h"

class AsylumEditor : public Asylum::Application
{
private:
	Asylum::Layer* mEditorLayer;
public:
	AsylumEditor() : Asylum::Application("Asylum Editor") { OnStartup(); }
	~AsylumEditor() { OnShutdown(); }

	virtual void OnStartup() override
	{
		// set window properties
		mWindow->SetVSync(false);

		// init all layers
		mEditorLayer = new EditorLayer();

		mLayerStack->PushLayer(mEditorLayer);

		// set event callbacks
		Asylum::Input::AddKeyPressedCallback(AM_BIND_FN_1(AsylumEditor::OnKeyPressed));
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
	return new AsylumEditor();
}