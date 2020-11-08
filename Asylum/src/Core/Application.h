#pragma once

#include "Graphics/Window.h"
#include "Graphics/Shader.h"
#include "Core/Layer.h"
#include "Core/LayerStack.h"

namespace Asylum {

	class Application
	{
	private:
		// delta time calc
		float mLastFrameTime = 0.0f;
		float mDeltaTime = 0.0f;

		// fps calc
		int mFpsCounter = 0;
		float mFpsTimer = 0.0f;
	protected:
		// core graphics
		Window* mWindow;

		LayerStack* mLayerStack;
	public:
		Application(const std::string& applicationName) { Init(applicationName); };
		virtual ~Application() { Shutdown(); };

		void Init(const std::string& applicationName);
		void Shutdown();
		void Run();
	protected:
		virtual void OnStartup() = 0;
		virtual void OnShutdown() = 0;
		virtual void OnUpdate(float dt) = 0;
	private:
		void UpdateAllLayers(float dt);
		void OnKeyPressed(int keycode);
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}
