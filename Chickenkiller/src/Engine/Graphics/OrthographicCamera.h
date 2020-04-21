#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine {

	class OrthographicCamera
	{
	private:
		glm::mat4 mViewMatrix;
		glm::mat4 mProjectionMatrix;

		glm::vec3 mPosition;
		float mRotation;
	public:
		OrthographicCamera();
		OrthographicCamera(float left, float right, float bottom, float top);
		OrthographicCamera(float left, float right, float bottom, float top, float zNear, float zFar);

		void SetPosition(const glm::vec3& position) { mPosition = position; RecalculateViewMatrix(); };
		void SetRotation(float rotation) { mRotation = rotation; RecalculateViewMatrix(); };

		inline const glm::vec3& GetPosition() const { return mPosition; };
		inline float GetRotation() const { return mRotation; };

		inline const glm::mat4& GetViewMatrix() const { return mViewMatrix; };
		inline const glm::mat4& GetProjectionMatrix() const { return mProjectionMatrix; };
	private:
		void RecalculateViewMatrix();
	};

}