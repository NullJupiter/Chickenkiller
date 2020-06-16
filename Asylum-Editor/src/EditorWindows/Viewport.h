#pragma once

#include <Asylum.h>

#include "EditorWindows/EditorWindow.h"
#include "ViewportCamera/ViewportCameraController.h"

class Viewport : public EditorWindow
{
private:
	ViewportCameraController mViewportCameraController;

	glm::vec2 mSize;
	Asylum::Ref<Asylum::Framebuffer> mViewportFB;
public:
	Viewport();
	
	void OnUpdate(float dt);
};