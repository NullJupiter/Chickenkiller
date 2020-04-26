#include "ampch.h"
#include "OrthographicCamera.h"

namespace Asylum {
	
	OrthographicCamera::OrthographicCamera()
		: mPosition(glm::vec3(0.0f)), mRotation(0.0f), mProjectionMatrix(glm::mat4(1.0f)), mViewMatrix(glm::mat4(1.0f))
	{}

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: mPosition(glm::vec3(0.0f)), mRotation(0.0f)
	{
		mProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		RecalculateViewMatrix();
	}

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float zNear, float zFar)
		: mPosition(glm::vec3(0.0f)), mRotation(0.0f)
	{
		mProjectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
		RecalculateViewMatrix();
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), mPosition);
		transform = glm::rotate(transform, glm::radians(mRotation), glm::vec3(0.0f, 0.0f, 1.0f));

		mViewMatrix = glm::inverse(transform);
	}

}