#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Asylum {

	class OrthographicCamera
	{
	private:
		glm::mat4 mViewMatrix;
		glm::mat4 mProjectionMatrix;
		glm::mat4 mViewProjectionMatrix;

		glm::vec2 mPosition;
		float mRotation;


	public:
		OrthographicCamera(float left, float right, float bottom, float top, float zNear = -1.0f, float zFar = 1.0f);

		void SetProjection(float left, float right, float bottom, float top, float zNear = -1.0f, float zFar = 1.0f);

		void SetPosition(const glm::vec2& position) { mPosition = position; RecalculateViewMatrix(); };
		void SetRotation(float angle) { mRotation = angle; RecalculateViewMatrix(); };

		inline const glm::vec2& GetPosition() const { return mPosition; };
		inline float GetRotation() const { return mRotation; };

		inline const glm::mat4& GetViewMatrix() const { return mViewMatrix; };
		inline const glm::mat4& GetProjectionMatrix() const { return mProjectionMatrix; };
		inline const glm::mat4& GetViewProjectionMatrix() const { return mViewProjectionMatrix; };
	private:
		void RecalculateViewMatrix();
	};

}