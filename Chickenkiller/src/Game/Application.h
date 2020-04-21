#pragma once

#include "pch.h"
#include "Engine/Engine.h"

class Application
{
private:
	// singleton instance
	static Application* sInstance;

	// core graphics
	Engine::Window* mWindow;
	std::shared_ptr<Engine::Shader> mDefaultShader;

	// layers
	Engine::LayerStack* mLayerStack;
	Engine::Layer* mGameLayer;

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
