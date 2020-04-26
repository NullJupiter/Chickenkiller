#include "GameLayer.h"

#include "App.h"

GameLayer::GameLayer()
{
	// get default shader
	mDefaultShader = Asylum::ResourceManager::GetShader("default");
}

void GameLayer::OnAttach()
{
	LOG("[*] Game Layer Attached!");
	
	// create camera
	mCamera = Asylum::OrthographicCamera(0.0f, (float)Asylum::Window::Get()->GetWidth(), 0.0f, (float)Asylum::Window::Get()->GetHeight(), -100.0f, 100.0f);
	mDefaultShader->Bind();
	mDefaultShader->SetUniformMat4("uProjection", mCamera.GetProjectionMatrix());

	// get test texture
	mTestTexture = Asylum::ResourceManager::GetTexture("test-texture");
	
	mTestAnimations.push_back(Asylum::ResourceManager::GetAnimation("player-up"));
	mTestAnimations.push_back(Asylum::ResourceManager::GetAnimation("player-down"));
	mTestAnimations.push_back(Asylum::ResourceManager::GetAnimation("player-right"));
	mTestAnimations.push_back(Asylum::ResourceManager::GetAnimation("player-left"));
}

void GameLayer::OnUpdate(float dt)
{
	// bind shader
	mDefaultShader->Bind();

	// updating
	{
		// camera controls
		if (Asylum::Input::IsKeyPressed(GLFW_KEY_Q))
			mCamera.SetRotation(mCamera.GetRotation() - 50.0f * dt);
		if (Asylum::Input::IsKeyPressed(GLFW_KEY_E))
			mCamera.SetRotation(mCamera.GetRotation() + 50.0f * dt);
		if (Asylum::Input::IsKeyPressed(GLFW_KEY_W))
			mCamera.SetPosition(mCamera.GetPosition() + glm::vec3(0.0f, 500.0f * dt, 0.0f));
		if (Asylum::Input::IsKeyPressed(GLFW_KEY_S))
			mCamera.SetPosition(mCamera.GetPosition() - glm::vec3(0.0f, 500.0f * dt, 0.0f));
		if (Asylum::Input::IsKeyPressed(GLFW_KEY_A))
			mCamera.SetPosition(mCamera.GetPosition() - glm::vec3(500.0f * dt, 0.0f, 0.0f));
		if (Asylum::Input::IsKeyPressed(GLFW_KEY_D))
			mCamera.SetPosition(mCamera.GetPosition() + glm::vec3(500.0f * dt, 0.0f, 0.0f));
		
		// update view matrix
		mDefaultShader->SetUniformMat4("uView", mCamera.GetViewMatrix());

		// update test animation
		for (auto& animation : mTestAnimations)
			animation->OnUpdate(dt);
	}

	// rendering
	{
		Asylum::Renderer::BeginDraw();

		for (uint32_t i = 0; i < mTestAnimations.size(); i++)
			Asylum::Renderer::DrawAnimatedRect({ i*150.0f + 30.0f, 300.0f }, { 122.22f, 122.25f }, 20.0f, mTestAnimations[i]);

		Asylum::Renderer::DrawTexturedRect({ 700.0f, 300.0f }, { 350.0f, 150.0f }, Asylum::ResourceManager::GetTextureAtlas("test-texture-atlas")->GetID());

		Asylum::Renderer::EndDraw();
	}
}

void GameLayer::OnDetach()
{
	LOG("[*] Game Layer Detached!");
}
