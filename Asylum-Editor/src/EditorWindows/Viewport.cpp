#include "Viewport.h"

#include <imgui.h>

Viewport::Viewport()
{
	mSize = { 0.0f, 0.0f };
	mViewportFB = Asylum::CreateRef<Asylum::Framebuffer>(Asylum::FramebufferSpecs(Asylum::Window::Get()->GetWidth(), Asylum::Window::Get()->GetHeight()));
}

void Viewport::OnUpdate(float dt)
{
	static Asylum::OrthographicCameraController* cameraController = Asylum::OrthographicCameraController::Get();
	
	// create imgui window
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("Viewport");
	ImGui::PopStyleVar();
	mIsWindowActive = ImGui::IsWindowFocused();

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

	// stop rendering to viewport
	Asylum::Renderer::UnbindFramebuffer();

	// render framebuffer to viewport window
	ImVec2 pos = ImGui::GetCursorScreenPos();
	uint32_t framebufferTexture = mViewportFB->GetColorAttachment();
	ImGui::GetWindowDrawList()->AddImage((void*)framebufferTexture, ImVec2(pos.x, pos.y), ImVec2(pos.x + mSize.x, pos.y + mSize.y), ImVec2(0, 1), ImVec2(1, 0));

	// end imgui window
	ImGui::End();
}