#include "TextureList.h"

#include <imgui.h>

#include "EditorWindows/WindowStateManager.h"

TextureList::TextureList()
{
}

void TextureList::OnUpdate(float dt)
{
	ImGui::Begin("Textures");

	const std::unordered_map<std::string, Asylum::Ref<Asylum::Texture>>& textures = Asylum::ResourceManager::GetAllTextureData();
	for (auto& textureData : textures)
	{
		if (ImGui::ImageButton((void*)textureData.second->GetID(), ImVec2(128, 128), ImVec2(0, 1), ImVec2(1, 0)))
			WindowStateManager::SetSelectedTexture(textureData.second);
		ImGui::Text(textureData.first.c_str());
	}

	static bool gridState = false;
	ImGui::Checkbox("Toggle Grid", &gridState);
	WindowStateManager::IsGridOn(gridState);

	ImGui::End();
}
