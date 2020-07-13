#include "TextureList.h"

#include <imgui.h>

TextureList::TextureList()
{
	mCurrentlySelectedTexture = nullptr;
}

void TextureList::OnUpdate(float dt)
{
	ImGui::Begin("Entity List");

	const std::unordered_map<std::string, Asylum::Ref<Asylum::Texture>>& textures = Asylum::ResourceManager::GetAllTextureData();
	for (auto& textureData : textures)
	{
		if (ImGui::ImageButton((void*)textureData.second->GetID(), ImVec2(128, 128), ImVec2(0, 1), ImVec2(1, 0)))
			mCurrentlySelectedTexture = textureData.second;
		ImGui::Text(textureData.first.c_str());
	}

	ImGui::End();
}
