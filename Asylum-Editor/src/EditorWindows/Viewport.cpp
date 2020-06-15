#include "Viewport.h"

#include <imgui.h>
#include "ViewportCamera/ViewportCameraController.h"

Viewport::Viewport()
{
	mSize = { 0.0f, 0.0f };
	ViewportCameraController::Get()->Init(mSize);
	
	mViewportFB = Asylum::CreateRef<Asylum::Framebuffer>(Asylum::FramebufferSpecs(Asylum::Window::Get()->GetWidth(), Asylum::Window::Get()->GetHeight()));
}

void Viewport::OnUpdate(float dt)
{
	static Asylum::OrthographicCameraController* cameraController = Asylum::OrthographicCameraController::Get();
	static ViewportCameraController* viewportCameraController = ViewportCameraController::Get();

	// update the vieport camera controller for movement in the viewport
	viewportCameraController->OnUpdate(dt, mSize);

	// create imgui window
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("Viewport");
	ImGui::PopStyleVar();
	mIsActive = ImGui::IsWindowFocused();

	// update size and projection matrix
	ImVec2 windowSize = ImGui::GetWindowSize();
	if (windowSize.x != mSize.x || windowSize.y != mSize.y)
		cameraController->UpdateProjection(windowSize.x / windowSize.y);

	mSize.x = windowSize.x;
	mSize.y = windowSize.y;

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
	ImVec2 pos = ImGui::GetCursorScreenPos();
	uint32_t framebufferTexture = mViewportFB->GetColorAttachment();
	ImGui::GetWindowDrawList()->AddImage((void*)framebufferTexture, ImVec2(pos.x, pos.y), ImVec2(pos.x + mSize.x, pos.y + mSize.y), ImVec2(0, 1), ImVec2(1, 0));

	// end imgui window
	ImGui::End();
}