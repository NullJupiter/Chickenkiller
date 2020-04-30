#pragma once

#include "Graphics/OrthographicCamera.h"
#include "Core/Input.h"
namespace Asylum {

	class OrthographicCameraController
	{
	private:
		float mAspectRatio;
		float mZoomLevel = 1.0f;
		OrthographicCamera mCamera;

		bool mRotation;
		int mCounter = 0;
		glm::vec3 mCameraPosition;
		float mCameraRotation;
		float mCameraTranslationSpeed, mCameraRotationSpeed;

		bool mShouldUpdateProjection = false;
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(float dt);

		inline OrthographicCamera& GetCamera() { return mCamera; };
		inline const OrthographicCamera& GetCamera() const { return mCamera; };

		inline float GetZoomLevel() const { return mZoomLevel; };
		void SetZoomLevel(float zoomLevel) { mZoomLevel = zoomLevel; };
	};

}