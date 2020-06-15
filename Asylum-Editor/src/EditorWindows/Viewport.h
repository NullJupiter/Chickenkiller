#pragma once

#include <Asylum.h>

#include "EditorWindows/EditorWindow.h"

class Viewport : public EditorWindow
{
private:
	glm::vec2 mSize;
	Asylum::Ref<Asylum::Framebuffer> mViewportFB;
public:
	Viewport();
	
	void OnUpdate(float dt);
};