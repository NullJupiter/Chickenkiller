#include "ViewportCameraController.h"


ViewportCameraController::ViewportCameraController()
{
	Asylum::OrthographicCameraController* cameraController = Asylum::OrthographicCameraController::Get();
	cameraController->SetZoomLevel(3.0f);
	cameraController->SetMinZoomLevel(0.5f);
	cameraController->SetMaxZoomLevel(10.0f);

	mViewportSize = {0.0f, 0.0f};
	mCameraPosition = { 0.0f, 0.0f };
	mCameraRotation = 0.0f;
	mCameraRotationSpeed = 180.0f;
	mCameraTranslationSpeed = cameraController->GetZoomLevel();
}

void ViewportCameraController::OnUpdate(float dt, const glm::vec2& viewportSize)
{
	// check inputs
	if (Asylum::Input::IsKeyPressed(AM_KEY_A))
	{
		mCameraPosition.x -= cos(glm::radians(mCameraRotation)) * mCameraTranslationSpeed * dt;
		mCameraPosition.y -= sin(glm::radians(mCameraRotation)) * mCameraTranslationSpeed * dt;
	}
	else if (Asylum::Input::IsKeyPressed(AM_KEY_D))
	{
		mCameraPosition.x += cos(glm::radians(mCameraRotation)) * mCameraTranslationSpeed * dt;
		mCameraPosition.y += sin(glm::radians(mCameraRotation)) * mCameraTranslationSpeed * dt;
	}
	else if (Asylum::Input::IsKeyPressed(AM_KEY_W))
	{
		mCameraPosition.x += -sin(glm::radians(mCameraRotation)) * mCameraTranslationSpeed * dt;
		mCameraPosition.y += cos(glm::radians(mCameraRotation)) * mCameraTranslationSpeed * dt;
	}
	else if (Asylum::Input::IsKeyPressed(AM_KEY_S))
	{
		mCameraPosition.x -= -sin(glm::radians(mCameraRotation)) * mCameraTranslationSpeed * dt;
		mCameraPosition.y -= cos(glm::radians(mCameraRotation)) * mCameraTranslationSpeed * dt;
	}

	// check rotation if activated
	if (Asylum::Input::IsKeyPressed(AM_KEY_Q))
		mCameraRotation += mCameraRotationSpeed * dt;
	if (Asylum::Input::IsKeyPressed(AM_KEY_E))
		mCameraRotation -= mCameraRotationSpeed * dt;

	if (mCameraRotation > 180.0f)
		mCameraRotation -= 360.0f;
	else if (mCameraRotation <= -180.0f)
		mCameraRotation += 360.0f;


	static Asylum::OrthographicCameraController* cameraController = Asylum::OrthographicCameraController::Get();

	if (mViewportSize != viewportSize)
	{
		mViewportSize = viewportSize;
		cameraController->UpdateProjection(mViewportSize.x / mViewportSize.y);
	}

	cameraController->SetCameraPosition(mCameraPosition);
	cameraController->SetCameraRotation(mCameraRotation);

	mCameraTranslationSpeed = cameraController->GetZoomLevel();
}