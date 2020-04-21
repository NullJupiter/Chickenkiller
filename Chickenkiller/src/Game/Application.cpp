#include "pch.h"
#include "Application.h"

// include all layers
#include "Game/Layers/GameLayer.h"

Application* Application::sInstance = nullptr;

Application* Application::Get()
{
	if (!sInstance) sInstance = new Application();
	return sInstance;
}

void Application::Init()
{
	// create window
	mWindow = Engine::Window::Get();
	mWindow->Init(Engine::WindowProps("Chickenkiller"));
	mWindow->SetClearColor(45, 57, 68);
	mWindow->SetVSync(false);

	// init renderer
	Engine::Renderer::Init();

	// load resources
	Engine::ResourceManager::LoadResources("res/config");

	// load shader
	mDefaultShader = Engine::ResourceManager::GetShader("default");
	mDefaultShader->Bind();
	// set texture slots array
	int samplers[8];
	for (int i = 0; i < 8; i++)
		samplers[i] = i;
	mDefaultShader->SetUniformIntArray("uTextures", 8, samplers);

	// init layer stack
	mLayerStack = new Engine::LayerStack();

	// init game layer
	mGameLayer = new GameLayer();

	// push first layer
	mLayerStack->PushLayer(mGameLayer);
}

void Application::Shutdown()
{
	delete mLayerStack;

	// unload resources
	Engine::ResourceManager::UnloadResources();

	// shut down the renderer
	Engine::Renderer::Shutdown();

	// shut down the window
	mWindow->Shutdown();

	delete sInstance;
}

void Application::Run()
{
	// game loop
	while (!mWindow->IsClosed())
	{
		mWindow->Clear();
		OnUpdate();
		mWindow->OnUpdate();
	}
}

void Application::OnUpdate()
{
	// calc delta time
	float thisFrameTime = (float)glfwGetTime();
	mDeltaTime = thisFrameTime - mLastFrameTime;
	mLastFrameTime = thisFrameTime;

	// calc frames per second (fps)
	mFpsCounter++;
	mFpsTimer += mDeltaTime;
	if (mFpsTimer >= 1.0f)
	{
		LOG("FPS: " << mFpsCounter);
		mFpsCounter = 0;
		mFpsTimer = 0.0f;
	}

	// update all layers
	for (auto& layer : *mLayerStack)
		layer->OnUpdate(mDeltaTime);

	if (Engine::Input::IsKeyPressed(GLFW_KEY_ESCAPE))
		mWindow->Close();
}
