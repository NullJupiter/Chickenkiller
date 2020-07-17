#include "ResourceTree.h"

#include <imgui.h>

#include "EditorWindows/WindowStateManager.h"

ResourceTree::ResourceTree()
{
}

void ResourceTree::OnUpdate(float dt)
{
	ImGui::Begin("Resources");

	if (ImGui::TreeNodeEx("Textures", ImGuiTreeNodeFlags_DefaultOpen))
	{
		const std::unordered_map<std::string, Asylum::Ref<Asylum::Texture>>& textures = Asylum::ResourceManager::GetAllTextureData();
		ImGui::Columns(4);
		ImGui::Separator();
		uint32_t i = 0;
		for (auto& textureData : textures)
		{
			if (i > 0 && i % 4 == 0) ImGui::Separator();
			if (ImGui::ImageButton((void*)textureData.second->GetID(), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().x), ImVec2(0, 1), ImVec2(1, 0), 0))
				WindowStateManager::SetSelectedTexture(textureData.second);
			ImGui::TextWrapped(textureData.first.c_str());

			i++;
			ImGui::NextColumn();
		}

		ImGui::Columns(1);
		ImGui::Separator();

		ImGui::TreePop();
	}

	if (ImGui::TreeNodeEx("Animations", ImGuiTreeNodeFlags_DefaultOpen))
	{
		const std::unordered_map<std::string, Asylum::Ref<Asylum::AnimationSheet>>& animationSheets = Asylum::ResourceManager::GetAllAnimationSheetData();
		for (auto& animationSheet : animationSheets)
		{
			if (ImGui::TreeNodeEx(animationSheet.first.c_str()))
			{
				ImGui::Columns(4);
				ImGui::Separator();
				uint32_t i = 0;
				for (auto& animation : animationSheet.second->GetAnimations())
				{
					animation.second->OnUpdate(dt);
					if (i > 0 && i % 4 == 0) ImGui::Separator();

					const std::array<glm::vec2, 4>& currentTexCoords = animation.second->GetCurrentTextureCoords();
					if (ImGui::ImageButton((void*)animationSheet.second->GetID(), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().x), ImVec2(currentTexCoords[2].x, currentTexCoords[2].y), ImVec2(currentTexCoords[0].x, currentTexCoords[0].y), 0))
					{
					}
					ImGui::TextWrapped(animation.first.c_str());

					i++;
					ImGui::NextColumn();
				}
				ImGui::TreePop();
			}
		}

		ImGui::Columns(1);
		ImGui::Separator();

		ImGui::TreePop();
	}

	static bool gridState = false;
	ImGui::Checkbox("Toggle Grid", &gridState);
	WindowStateManager::IsGridOn(gridState);

	ImGui::End();
}
