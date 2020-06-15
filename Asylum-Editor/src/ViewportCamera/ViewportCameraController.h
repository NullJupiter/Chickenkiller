#pragma once

#include <Asylum.h>

class ViewportCameraController
{
private:
	static ViewportCameraController* sInstance;

	glm::vec2 mViewportSize;
	glm::vec2 mCameraPosition;
	float mCameraRotation;
	float mCameraRotationSpeed;
	float mCameraTranslationSpeed;
public:
	static ViewportCameraController* Get();

	void Init(const glm::vec2& viewportSize);
	void OnUpdate(float dt, const glm::vec2& viewportSize);
private:
	ViewportCameraController() {};
	~ViewportCameraController() = default;
};