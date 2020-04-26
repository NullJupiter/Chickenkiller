#pragma once

#include "Asylum.h"

class Application
{
private:
	// singleton instance
	static Application* sInstance;

	// core graphics
	Asylum::Window* mWindow;
	std::shared_ptr<Asylum::Shader> mDefaultShader;

	// layers
	Asylum::LayerStack* mLayerStack;
	Asylum::Layer* mGameLayer;

	// delta time calc
	float mLastFrameTime = 0.0f;
	float mDeltaTime = 0.0f;

	// fps calc
	int mFpsCounter = 0;
	float mFpsTimer = 0.0f;
public:
	static Application* Get();

	void Init();
	void Shutdown();

	void Run();
private:
	Application() : mWindow(nullptr), mGameLayer(nullptr), mLayerStack(nullptr) {};
	~Application() = default;
	
	void OnUpdate();
};
