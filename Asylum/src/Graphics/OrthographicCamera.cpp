#include "ampch.h"
#include "OrthographicCamera.h"

namespace Asylum {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float zNear, float zFar)
		: mPosition(glm::vec3(0.0f)), mRotation(0.0f), mViewMatrix(1.0f)
	{
		SetProjection(left, right, bottom, top, zNear, zFar);
		RecalculateViewMatrix();
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		mProjectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
		mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), {mPosition.x, mPosition.y, 0.0f});
		transform = glm::rotate(transform, glm::radians(mRotation), glm::vec3(0.0f, 0.0f, 1.0f));

		mViewMatrix = glm::inverse(transform);
		mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;
	}

}