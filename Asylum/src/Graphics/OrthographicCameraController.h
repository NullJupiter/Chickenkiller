#pragma once

#include "Graphics/OrthographicCamera.h"
#include "Core/Input.h"
namespace Asylum {

	class OrthographicCameraController
	{
	private:
		static OrthographicCameraController* sInstance;
	protected:
		float mAspectRatio;
		float mZoomLevel = 1.0f;
		float mMinZoomLevel = 0.25f;
		float mMaxZoomLevel = 5.0f;
		OrthographicCamera* mCamera;

		glm::vec3 mCameraPosition;
		float mCameraRotation;
	public:
		static OrthographicCameraController* Get();

		void Init(float aspectRatio);

		void OnUpdate(float dt);
		void UpdateProjection(float aspectRatio);

		inline void SetCameraPosition(const glm::vec2& position) { mCamera->SetPosition(position); };
		inline void SetCameraRotation(float angle) { mCamera->SetRotation(angle); };

		inline const glm::vec2& GetCameraPosition() const { return mCamera->GetPosition(); };
		inline float GetCameraRotation() const { return mCamera->GetRotation(); };

		inline const glm::mat4& GetViewProjectionMatrix() const { return mCamera->GetViewProjectionMatrix(); };

		inline float GetZoomLevel() const { return mZoomLevel; };
		void SetZoomLevel(float zoomLevel) { mZoomLevel = zoomLevel; };
		void SetMaxZoomLevel(float level) { mMaxZoomLevel = level; };
		void SetMinZoomLevel(float level) 
		{
			mMinZoomLevel = level;
			mZoomLevel = level;
			mCamera->SetProjection(-mAspectRatio * mZoomLevel, mAspectRatio * mZoomLevel, -mZoomLevel, mZoomLevel);
		};
	private:
		OrthographicCameraController() {};
		~OrthographicCameraController() = default;

		void OnMouseScrolled(float xoffset, float yoffset);
		void OnWindowResized(int width, int height);
	};

}