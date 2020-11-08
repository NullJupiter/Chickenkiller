#include "Viewport.h"

#include <imgui.h>
#include "ViewportCamera/ViewportCameraController.h"
#include "EditorWindows/WindowStateManager.h"

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
	ImVec2 contentRegionSize = ImGui::GetContentRegionAvail();
	if (contentRegionSize.x != mSize.x || contentRegionSize.y != mSize.y)
	{
		Asylum::Window::Get()->SetViewport(0, 0, (uint32_t)contentRegionSize.x, (uint32_t)contentRegionSize.y);
		mViewportFB->Resize((uint32_t)contentRegionSize.x, (uint32_t)contentRegionSize.y);

		mSize.x = contentRegionSize.x;
		mSize.y = contentRegionSize.y;
	}


	// render to viewport
	Asylum::Renderer::BindFramebuffer(mViewportFB);
	Asylum::Window::Get()->Clear();

	// render stuff to framebuffer
	// update and render all entities
	Asylum::EntitySystem::OnUpdate(dt);
	Asylum::EntitySystem::OnRender();

	Asylum::ResourceManager::GetShader("default")->Bind();
	Asylum::Renderer::BeginDraw();

    ImVec2 windowPos = ImGui::GetWindowPos();
	ImVec2 windowSize = ImGui::GetWindowSize();
	ImVec2 mousePos = ImGui::GetMousePos();
	glm::vec2 relMousePos = { mousePos.x - windowPos.x, mousePos.y - windowPos.y - 18.0f };
	glm::vec2 mouseWorldPosition = Asylum::Utils::Raycast::CastMousePosition(relMousePos, *(glm::vec2*)&windowSize);

	if (WindowStateManager::IsGridOn())
		mouseWorldPosition = { round(mouseWorldPosition.x), round(mouseWorldPosition.y) };
	Asylum::Renderer::DrawRectangle(mouseWorldPosition, { 1,1 }, WindowStateManager::GetSelectedTexture());

	Asylum::Renderer::EndDraw();

	// stop rendering to viewport
	Asylum::Renderer::UnbindFramebuffer();

	// render framebuffer to viewport window
	uint32_t framebufferTexture = mViewportFB->GetColorAttachment();
	ImGui::Image((void*)framebufferTexture, ImVec2{ mSize.x, mSize.y }, ImVec2{ 0,1 }, ImVec2{ 1,0 });

	// end imgui window
	ImGui::End();
}
