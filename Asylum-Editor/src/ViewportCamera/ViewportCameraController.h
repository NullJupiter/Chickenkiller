#pragma once

#include <Asylum.h>

class ViewportCameraController
{
private:
	glm::vec2 mViewportSize;
	glm::vec2 mCameraPosition;
	float mCameraRotation;
	float mCameraRotationSpeed;
	float mCameraTranslationSpeed;
public:
	ViewportCameraController();

	void OnUpdate(float dt, const glm::vec2& viewportSize);
};