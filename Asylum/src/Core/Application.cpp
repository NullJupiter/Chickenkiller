#include "ampch.h"
#include "Application.h"

#include "Graphics/Renderer.h"
#include "Core/ResourceManager.h"
#include "Core/Entity/EntitySystem.h"
#include "Editor/ImGuiManager.h"
#include "Core/KeyCodes.h"
#include "Editor/Editor.h"
#include "Graphics/OrthographicCameraController.h"

namespace Asylum {

	void Application::Init()
	{
		// create window
		mWindow = Window::Get();
		mWindow->Init(WindowProps("Asylum Engine"));
		mWindow->SetClearColor(45, 57, 68);

		// event callbacks
		Input::AddKeyPressedCallback(AM_BIND_FN_1(Application::OnKeyPressed));

		// init renderer
		Renderer::Init();

#ifdef AM_DEBUG
		// init imgui
		ImGuiManager::Init();
#endif

		// load resources
		ResourceManager::LoadResources("res/config");

		// init entity system
		EntitySystem::Init();

		// load shader
		Ref<Shader> defaultShader = ResourceManager::GetShader("default");
		defaultShader->Bind();
		// set texture slots array
		int samplers[8];
		for (int i = 0; i < 8; i++)
			samplers[i] = i;
		defaultShader->SetUniformIntArray("uTextures", 8, samplers);

		// init camera controller
		OrthographicCameraController::Get()->Init((float)Window::Get()->GetWidth() / (float)Window::Get()->GetHeight());

		// init layer stack
		mLayerStack = new LayerStack();
	}

	void Application::Shutdown()
	{
		delete mLayerStack;

		// unload resources
		ResourceManager::UnloadResources();

#ifdef AM_DEBUG
		// shut imgui down
		ImGuiManager::Shutdown();
#endif

		// shut down the renderer
		Renderer::Shutdown();

		// shut down the window
		mWindow->Shutdown();
	}

	void Application::Run()
	{
		// game loop
		while (!mWindow->IsClosed())
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

			// clear the frame buffer
			mWindow->Clear();

			// update the camera controller
			OrthographicCameraController::Get()->OnUpdate(mDeltaTime);


			// update all layers in layer stack
			Editor::BeginCustomRender();
			UpdateAllLayers(mDeltaTime);
			Editor::EndCustomRender();

			// call client update method for application control
			OnUpdate(mDeltaTime);
			
			// update the window
			mWindow->OnUpdate();
		}
	}

	void Application::UpdateAllLayers(float dt)
	{
		for (auto& layer : *mLayerStack)
			layer->OnUpdate(mDeltaTime);
	}

	void Application::OnKeyPressed(int keycode)
	{
		if (keycode == AM_KEY_F1)
		{
			Editor::SetEditorIsActive(!Editor::IsEditorActive());
		}
	}
}