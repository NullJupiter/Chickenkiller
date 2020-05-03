#include "ampch.h"
#include "EditorLayer.h"

#include "imgui.h"

#include "Editor/ImGuiManager.h"
#include "Graphics/Window.h"
#include "Graphics/Renderer.h"
#include "Core/Entity/EntitySystem.h"

namespace Asylum {

	void EditorLayer::OnAttach()
	{
		mIsGameRunning = true;
		mGameWindowSize = { 0.0f, 0.0f };

		mCameraController = CreateScope<OrthographicCameraController>(16.0f / 9.0f, true);
	}

	void EditorLayer::OnDetach()
	{

	}

	void EditorLayer::OnUpdate(float dt)
	{
		ImGuiManager::Begin();
		ImGui::DockSpaceOverViewport();

		// demo window
		{
			ImGui::ShowDemoWindow();
		}

		// game rendering window
		{
			ImGui::Begin("Game");
			
			ImVec2 pos = ImGui::GetCursorScreenPos();
			ImVec2 windowSize = ImGui::GetWindowSize();
			if (windowSize.x != mGameWindowSize.x || windowSize.y != mGameWindowSize.y)
				mCameraController->UpdateProjection(windowSize.x / windowSize.y);

			mGameWindowSize.x = windowSize.x;
			mGameWindowSize.y = windowSize.y;

			// update
			{
				if (mIsGameRunning)
				{
					mCameraController->OnUpdate(dt);
					EntitySystem::OnUpdate(dt);
				}
			}

			// rendering
			{
				if (mIsGameRunning)
				{
					Renderer::DrawToFramebuffer(true);
					Window::Get()->Clear();

					EntitySystem::OnRender(mCameraController);

					Renderer::DrawToFramebuffer(false);
				}
			}

			uint32_t framebufferTexture = Renderer::GetFramebufferRender();
			ImGui::GetWindowDrawList()->AddImage((void*)framebufferTexture, ImVec2(pos.x, pos.y), ImVec2(pos.x + mGameWindowSize.x, pos.y + mGameWindowSize.y), ImVec2(0, 1), ImVec2(1, 0));
			
			ImGui::End();
		}

		ImGuiManager::End();
	}


}