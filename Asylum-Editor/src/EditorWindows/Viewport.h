#pragma once

#include <Asylum.h>

class Viewport
{
private:
	glm::vec2 mSize;
	bool mIsWindowActive = true;
	Asylum::Ref<Asylum::Framebuffer> mViewportFB;
public:
	Viewport();
	
	void OnUpdate(float dt);
};