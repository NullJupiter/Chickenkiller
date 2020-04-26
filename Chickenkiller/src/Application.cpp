#include "Application.h"

// include all layers
#include "Layers/GameLayer.h"

Application* Application::sInstance = nullptr;

Application* Application::Get()
{
	if (!sInstance) sInstance = new Application();
	return sInstance;
}

void Application::Init()
{
	// create window
	mWindow = Asylum::Window::Get();
	mWindow->Init(Asylum::WindowProps("Chickenkiller"));
	mWindow->SetClearColor(45, 57, 68);
	mWindow->SetVSync(false);

	// init renderer
	Asylum::Renderer::Init();

	// load resources
	Asylum::ResourceManager::LoadResources("res/config");

	// load shader
	mDefaultShader = Asylum::ResourceManager::GetShader("default");
	mDefaultShader->Bind();
	// set texture slots array
	int samplers[8];
	for (int i = 0; i < 8; i++)
		samplers[i] = i;
	mDefaultShader->SetUniformIntArray("uTextures", 8, samplers);

	// init layer stack
	mLayerStack = new Asylum::LayerStack();

	// init game layer
	mGameLayer = new GameLayer();

	// push first layer
	mLayerStack->PushLayer(mGameLayer);
}

void Application::Shutdown()
{
	delete mLayerStack;

	// unload resources
	Asylum::ResourceManager::UnloadResources();

	// shut down the renderer
	Asylum::Renderer::Shutdown();

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

	if (Asylum::Input::IsKeyPressed(GLFW_KEY_ESCAPE))
		mWindow->Close();
}
