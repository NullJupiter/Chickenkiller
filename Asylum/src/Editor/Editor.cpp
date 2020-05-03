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
		bool IsGameWindowActive = false;
		glm::vec2 GameWindowSize = { 0.0f, 0.0f };
	};
	static EditorData sData;

	void Editor::BeginCustomRender(Scope<OrthographicCameraController>& cameraController)
	{
		if (sData.EditorIsActive)
		{
			// begin docking space and new frame
			ImGuiManager::Begin();
			ImGui::DockSpaceOverViewport();

			// render all imgui windows
			RenderMainMenu();
			RenderEntityListWindow();

			// begin game window
			ImGui::Begin("Game");
			sData.IsGameWindowActive = ImGui::IsWindowFocused();
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

	bool Editor::GetIsGameWindowActive()
	{
		return sData.IsGameWindowActive;
	}

	void Editor::RenderMainMenu()
	{
		static bool showAboutWindow = false;
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Asylum"))
			{
				if (ImGui::MenuItem("About"))
					showAboutWindow = !showAboutWindow;

				if (ImGui::MenuItem("Quit"))
					Window::Get()->Close();

				ImGui::EndMenu();
			}
			
			static bool windowIsFullscreen = false;
			if (ImGui::BeginMenu("View"))
			{
				if (!windowIsFullscreen)
				{
					if (ImGui::MenuItem("Switch to Fullscreen Mode"))
					{
						windowIsFullscreen = true;
						Window::Get()->SetFullscreenMode();
					}
				}
				else
				{
					if (ImGui::MenuItem("Switch to Windowed Mode"))
					{
						windowIsFullscreen = false;
						Window::Get()->SetWindowedMode(100, 100, Window::Get()->GetWidth()/2, Window::Get()->GetHeight()/2);
					}
				}

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		if (showAboutWindow)
		{
			ImGui::Begin("About", &showAboutWindow);
			ImGui::Text("Asylum Engine - v1.0");
			ImGui::Text("Created by Mark Haube");
			ImGui::Text("Copyright 2020 - All rights reserved.");
			ImGui::End();
		}
	}

	void Editor::RenderEntityListWindow()
	{
		ImGui::Begin("Entity List View");

		// get all entity data
		const std::vector<EntityData>& entitiesData = EntitySystem::GetAllEntityData();
		static const char* currentEntity = NULL;
		if (ImGui::BeginCombo("Entities", currentEntity))
		{
			for (uint32_t i = 0; i < entitiesData.size(); i++)
			{
				bool isSelected = (currentEntity == entitiesData[i].EntityName.c_str());
				if (ImGui::Selectable(entitiesData[i].EntityName.c_str(), isSelected))
					currentEntity = entitiesData[i].EntityName.c_str();
				if (isSelected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
		ImGui::End();
	}

}

#endif