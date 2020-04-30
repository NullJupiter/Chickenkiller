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
	
	// create camera controller
	mCameraController = std::make_unique<Asylum::OrthographicCameraController>(16.0f / 9.0f, true);
	
	// set matrices
	mDefaultShader->Bind();
	mDefaultShader->SetUniformMat4("uViewProjection", mCameraController->GetCamera().GetViewProjectionMatrix());

	// get test texture
	mTestTexture = Asylum::ResourceManager::GetTexture("test-texture");
}

void GameLayer::OnUpdate(float dt)
{
	// bind shader
	mDefaultShader->Bind();

	static auto testAnimation = Asylum::ResourceManager::GetAnimation("player-right");

	// updating
	{
		// update the camera controller
		mCameraController->OnUpdate(dt);

		// update view projection matrix
		mDefaultShader->SetUniformMat4("uViewProjection", mCameraController->GetCamera().GetViewProjectionMatrix());

		testAnimation->OnUpdate(dt);
	}

	// rendering
	{
		Asylum::Renderer::BeginDraw();

		Asylum::Renderer::DrawColoredRect({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 255,255,255,255 });
		Asylum::Renderer::DrawRotatedColoredRect({ 0.5f, 2.5f }, { 1.0f, 1.0f }, { 200, 100, 255, 255 }, glm::radians((float)glfwGetTime()*100.0f));

		Asylum::Renderer::DrawTexturedRect({ 2.0f, 0.0f }, { 1.0f, 1.0f }, mTestTexture);
		Asylum::Renderer::DrawRotatedTexturedRect({ 2.5f, 2.5f }, { 1.0f, 1.0f }, mTestTexture, glm::radians((float)glfwGetTime()*100.0f));

		Asylum::Renderer::DrawAnimatedRect({ 4.0f, 0.0f }, { 1.0f, 1.0f }, testAnimation);
		Asylum::Renderer::DrawRotatedAnimatedRect({ 4.5f, 2.5f }, { 1.0f, 1.0f }, glm::radians((float)glfwGetTime() * 100.0f), testAnimation);

		Asylum::Renderer::EndDraw();
	}
}

void GameLayer::OnDetach()
{
	LOG("[*] Game Layer Detached!");
}
