#pragma once

#include "Graphics/OrthographicCamera.h"
#include "Core/Input.h"
namespace Asylum {

	class OrthographicCameraController
	{
	private:
		static OrthographicCameraController* sInstance;

		float mAspectRatio;
		float mZoomLevel = 1.0f;
		float mMinZoomLevel = 0.25f;
		float mMaxZoomLevel = 5.0f;
		OrthographicCamera* mCamera;

		bool mRotation;
		int mCounter = 0;
		glm::vec3 mCameraPosition;
		float mCameraRotation;
		float mCameraTranslationSpeed, mCameraRotationSpeed;

		bool mShouldUpdateProjection = false;
	public:
		static OrthographicCameraController* Get();

		void Init(float aspectRatio, bool rotation = false);

		void OnUpdate(float dt);
		void UpdateProjection(float aspectRatio);

		inline void SetCameraPosition(const glm::vec2& position) { mCamera->SetPosition(position); };
		inline void SetCameraRotation(float angle) { mCamera->SetRotation(angle); };

		inline const glm::vec2& GetCameraPosition() const { return mCamera->GetPosition(); };
		inline float GetCameraRotation() const { return mCamera->GetRotation(); };

		inline const glm::mat4& GetViewProjectionMatrix() const { return mCamera->GetViewProjectionMatrix(); };

		inline float GetZoomLevel() const { return mZoomLevel; };
		void SetZoomLevel(float zoomLevel) { mZoomLevel = zoomLevel; };
	private:
		OrthographicCameraController() {};
		~OrthographicCameraController() = default;

		void OnEditorUpdate(float dt);
		void OnGameUpdate(float dt);

		void OnMouseScrolled(float xoffset, float yoffset);
		void OnWindowResized(int width, int height);
	};

}