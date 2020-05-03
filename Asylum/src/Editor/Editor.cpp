#include "ampch.h"
#include "Editor.h"

#ifdef AM_DEBUG
#include "imgui.h"

#include "Editor/ImGuiManager.h"
#include "Graphics/Window.h"
#include "Graphics/Renderer.h"
#include "Core/Entity/EntitySystem.h"

namespace Asylum {

	struct EditorData
	{
		bool EditorIsActive = true;
		bool IsGameRunning = true;
		glm::vec2 GameWindowSize = { 0.0f, 0.0f };
	};
	static EditorData sData;

	void Editor::BeginCustomRender(Scope<OrthographicCameraController>& cameraController)
	{
		if (sData.EditorIsActive)
		{
			// begin docking space
			ImGuiManager::Begin();
			ImGui::DockSpaceOverViewport();

			// render all imgui windows
			RenderEntityListWindow();

			// begin game window
			ImGui::Begin("Game");

			ImVec2 windowSize = ImGui::GetWindowSize();
			if (windowSize.x != sData.GameWindowSize.x || windowSize.y != sData.GameWindowSize.y)
				cameraController->UpdateProjection(windowSize.x / windowSize.y);

			sData.GameWindowSize.x = windowSize.x;
			sData.GameWindowSize.y = windowSize.y;

			Renderer::DrawToFramebuffer(true);
			Window::Get()->Clear();
		}
	}

	void Editor::EndCustomRender()
	{
		if (sData.EditorIsActive)
		{
			Renderer::DrawToFramebuffer(false);

			ImVec2 pos = ImGui::GetCursorScreenPos();
			uint32_t framebufferTexture = Renderer::GetFramebufferRender();
			ImGui::GetWindowDrawList()->AddImage((void*)framebufferTexture, ImVec2(pos.x, pos.y), ImVec2(pos.x + sData.GameWindowSize.x, pos.y + sData.GameWindowSize.y), ImVec2(0, 1), ImVec2(1, 0));

			ImGui::End();
			ImGuiManager::End();
		}
	}

	void Editor::SetEditorIsActive(bool isActive)
	{
		sData.EditorIsActive = isActive;
	}

	void Editor::RenderEntityListWindow()
	{
		ImGui::Begin("Entity List View");

		// get all entity data
		const std::vector<EntityData>& entitiesData = EntitySystem::GetAllEntityData();
		ImGui::ListBoxHeader("Entities");
		for (auto entityData : entitiesData)
		{
			static bool selected = false;
			if (ImGui::Selectable(entityData.EntityName.c_str(), &selected))
			{

			}
		}
		ImGui::ListBoxFooter();

		ImGui::End();
	}

}

#endif