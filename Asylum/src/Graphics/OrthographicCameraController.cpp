#include "ampch.h"
#include "OrthographicCameraController.h"

#include "Core/KeyCodes.h"

namespace Asylum {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: mAspectRatio(aspectRatio), mRotation(rotation), mCamera(-mAspectRatio * mZoomLevel, mAspectRatio* mZoomLevel, -mZoomLevel, mZoomLevel)
	{
		// initialize parameters
		mZoomLevel = 1.0f;
		mCameraPosition = { 0.0f, 0.0f, 0.0f };
		mCameraRotation = 0.0f;
		
		mCameraTranslationSpeed = mZoomLevel;
		mCameraRotationSpeed = 180.0f;
		
		// set event callbacks
		Input::AddScrollCallback([this](float xoffset, float yoffset) 
			{
				mZoomLevel -= yoffset * 0.25f;
				mZoomLevel = std::max(mZoomLevel, 0.25f);
				mCamera.SetProjection(-mAspectRatio * mZoomLevel, mAspectRatio * mZoomLevel, -mZoomLevel, mZoomLevel);
			});
		Window::Get()->AddWindowResizeCallback([this](int width, int height)
			{
				mAspectRatio = (float)width / (float)height;
				mCamera.SetProjection(-mAspectRatio * mZoomLevel, mAspectRatio * mZoomLevel, -mZoomLevel, mZoomLevel);
			});
	}

	void OrthographicCameraController::OnUpdate(float dt)
	{
		// check inputs
		if (Input::IsKeyPressed(AM_KEY_A))
		{
			mCameraPosition.x -= cos(glm::radians(mCameraRotation)) * mCameraTranslationSpeed * dt;
			mCameraPosition.y -= sin(glm::radians(mCameraRotation)) * mCameraTranslationSpeed * dt;
		}
		else if (Input::IsKeyPressed(AM_KEY_D))
		{
			mCameraPosition.x += cos(glm::radians(mCameraRotation)) * mCameraTranslationSpeed * dt;
			mCameraPosition.y += sin(glm::radians(mCameraRotation)) * mCameraTranslationSpeed * dt;
		}
		else if (Input::IsKeyPressed(AM_KEY_W))
		{
			mCameraPosition.x += -sin(glm::radians(mCameraRotation)) * mCameraTranslationSpeed * dt;
			mCameraPosition.y += cos(glm::radians(mCameraRotation)) * mCameraTranslationSpeed * dt;
		}
		else if (Input::IsKeyPressed(AM_KEY_S))
		{
			mCameraPosition.x -= -sin(glm::radians(mCameraRotation)) * mCameraTranslationSpeed * dt;
			mCameraPosition.y -= cos(glm::radians(mCameraRotation)) * mCameraTranslationSpeed * dt;
		}

		// check rotation if activated
		if (mRotation)
		{
			if (Input::IsKeyPressed(AM_KEY_Q))
				mCameraRotation += mCameraRotationSpeed * dt;
			if (Input::IsKeyPressed(AM_KEY_E))
				mCameraRotation -= mCameraRotationSpeed * dt;

			if (mCameraRotation > 180.0f)
				mCameraRotation -= 360.0f;
			else if (mCameraRotation <= -180.0f)
				mCameraRotation += 360.0f;

			// set camera rotation
			mCamera.SetRotation(mCameraRotation);
		}

		// set camera position
		mCamera.SetPosition(mCameraPosition);

		mCameraTranslationSpeed = mZoomLevel;
	}

}