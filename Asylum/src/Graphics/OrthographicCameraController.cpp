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

	void OrthographicCameraController::Init(float aspectRatio)
	{
		// initialize parameters
		mAspectRatio = aspectRatio;
		mCamera = new OrthographicCamera(-mAspectRatio * mZoomLevel, mAspectRatio * mZoomLevel, -mZoomLevel, mZoomLevel);

		mZoomLevel = 1.0f;
		mCameraPosition = { 0.0f, 0.0f, 0.0f };
		mCameraRotation = 0.0f;
		
		// set event callbacks
		Input::AddScrollCallback(AM_BIND_FN_2(OrthographicCameraController::OnMouseScrolled));
		Window::Get()->AddWindowResizeCallback(AM_BIND_FN_2(OrthographicCameraController::OnWindowResized));
	}

	void OrthographicCameraController::OnUpdate(float dt)
	{
	}

	void OrthographicCameraController::UpdateProjection(float aspectRatio)
	{
		mAspectRatio = aspectRatio;
		mCamera->SetProjection(-mAspectRatio * mZoomLevel, mAspectRatio * mZoomLevel, -mZoomLevel, mZoomLevel);
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