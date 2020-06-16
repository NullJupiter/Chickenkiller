#include "Viewport.h"

#include <imgui.h>
#include "ViewportCamera/ViewportCameraController.h"

Viewport::Viewport()
{
	mViewportCameraController = ViewportCameraController();
	mSize = { 0.0f, 0.0f };

	mViewportFB = Asylum::CreateRef<Asylum::Framebuffer>(Asylum::FramebufferSpecs(Asylum::Window::Get()->GetWidth(), Asylum::Window::Get()->GetHeight()));
}

void Viewport::OnUpdate(float dt)
{
	// update the vieport camera controller for movement in the viewport
	mViewportCameraController.OnUpdate(dt, mSize);

	// create imgui window
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("Viewport");
	ImGui::PopStyleVar();
	mIsActive = ImGui::IsWindowFocused();

	// update size and projection matrix
	ImVec2 windowSize = ImGui::GetContentRegionAvail();
	if (windowSize.x != mSize.x || windowSize.y != mSize.y)
	{
		Asylum::Window::Get()->SetViewport(0, 0, (uint32_t)windowSize.x, (uint32_t)windowSize.y);
		mViewportFB->Resize((uint32_t)windowSize.x, (uint32_t)windowSize.y);

		mSize.x = windowSize.x;
		mSize.y = windowSize.y;
	}


	// render to viewport
	Asylum::Renderer::BindFramebuffer(mViewportFB);
	Asylum::Window::Get()->Clear();

	// render stuff to framebuffer
	// update and render all entities
	Asylum::EntitySystem::OnUpdate(dt);
	Asylum::EntitySystem::OnRender();

	// stop rendering to viewport
	Asylum::Renderer::UnbindFramebuffer();

	// render framebuffer to viewport window
	uint32_t framebufferTexture = mViewportFB->GetColorAttachment();
	ImGui::Image((void*)framebufferTexture, ImVec2{ mSize.x, mSize.y }, ImVec2{ 0,1 }, ImVec2{ 1,0 });

	// end imgui window
	ImGui::End();
}