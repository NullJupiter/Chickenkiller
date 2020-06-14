#include "ampch.h"
#include "OrthographicCameraController.h"

#include "Core/KeyCodes.h"

namespace Asylum {

	OrthographicCameraController* OrthographicCameraController::sInstance = nullptr;

	OrthographicCameraController* OrthographicCameraController::Get()
	{
		if (!sInstance) sInstance = new OrthographicCameraController();
		return sInstance;
	}

	void OrthographicCameraController::Init(float aspectRatio, bool rotation)
	{
		// initialize parameters
		mAspectRatio = aspectRatio;
		mRotation = rotation;
		mCamera = new OrthographicCamera(-mAspectRatio * mZoomLevel, mAspectRatio * mZoomLevel, -mZoomLevel, mZoomLevel);

		mZoomLevel = 1.0f;
		mCameraPosition = { 0.0f, 0.0f, 0.0f };
		mCameraRotation = 0.0f;
		
		mCameraTranslationSpeed = mZoomLevel;
		mCameraRotationSpeed = 180.0f;
		
		// set event callbacks
		Input::AddScrollCallback(AM_BIND_FN_2(OrthographicCameraController::OnMouseScrolled));
		Window::Get()->AddWindowResizeCallback(AM_BIND_FN_2(OrthographicCameraController::OnWindowResized));
	}

	void OrthographicCameraController::OnUpdate(float dt)
	{
		/*static bool setupEditorVars = true;
		static bool setupGameVars = true;

			// setup editor members when switched to editor mode
			if (setupEditorVars)
			{
				mZoomLevel = 3.0f;
				mMinZoomLevel = 0.5f;
				mMaxZoomLevel = 10.0f;
				const glm::vec2& gameWindowSize = Editor::GetGameWindowSize();
				UpdateProjection(gameWindowSize.x / gameWindowSize.y);
				setupEditorVars = false;
				setupGameVars = true;
			}
			
			OnEditorUpdate(dt);
		}
		else 
		{
			// setup game members when switched to game mode
			if (setupGameVars)
			{
				mCameraRotation = 0.0f;
				mZoomLevel = 3.0f;
				mMinZoomLevel = 2.0f;
				mMaxZoomLevel = 4.0f;
				UpdateProjection((float)Window::Get()->GetWidth() / (float)Window::Get()->GetHeight());
				setupGameVars = false;
				setupEditorVars = true;
			}

			OnGameUpdate(dt);
		}*/
	}

	void OrthographicCameraController::UpdateProjection(float aspectRatio)
	{
		mAspectRatio = aspectRatio;
		mCamera->SetProjection(-mAspectRatio * mZoomLevel, mAspectRatio * mZoomLevel, -mZoomLevel, mZoomLevel);
	}

	void OrthographicCameraController::OnEditorUpdate(float dt)
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
			mCamera->SetRotation(mCameraRotation);
		}

		// set camera position
		mCamera->SetPosition(mCameraPosition);

		mCameraTranslationSpeed = mZoomLevel;
	}

	void OrthographicCameraController::OnGameUpdate(float dt)
	{
		mCamera->SetRotation(mCameraRotation);
		mCamera->SetPosition(mCameraPosition);
	}

	void OrthographicCameraController::OnMouseScrolled(float xoffset, float yoffset)
	{
		mZoomLevel -= yoffset * 0.25f;
		mZoomLevel = std::max(mZoomLevel, mMinZoomLevel);
		mZoomLevel = std::min(mZoomLevel, mMaxZoomLevel);
		mCamera->SetProjection(-mAspectRatio * mZoomLevel, mAspectRatio * mZoomLevel, -mZoomLevel, mZoomLevel);
	}

	void OrthographicCameraController::OnWindowResized(int width, int height)
	{
		mAspectRatio = (float)width / (float)height;
		mCamera->SetProjection(-mAspectRatio * mZoomLevel, mAspectRatio * mZoomLevel, -mZoomLevel, mZoomLevel);
	}

}