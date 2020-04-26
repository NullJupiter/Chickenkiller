#pragma once

#include "Graphics/Window.h"
#include "Graphics/Shader.h"
#include "Core/Layer.h"
#include "Core/LayerStack.h"

namespace Asylum {

	class Application
	{
	private:
		// core graphics
		Window* mWindow;


		// delta time calc
		float mLastFrameTime = 0.0f;
		float mDeltaTime = 0.0f;

		// fps calc
		int mFpsCounter = 0;
		float mFpsTimer = 0.0f;
	protected:
		LayerStack* mLayerStack;
	public:
		Application() { Init(); };
		~Application() { Shutdown(); };

		void Init();
		void Shutdown();
		void Run();
	protected:
		virtual void OnStartup() = 0;
		virtual void OnShutdown() = 0;
		virtual void OnUpdate(float dt) = 0;
	private:
		void UpdateAllLayers(float dt);
	};

}