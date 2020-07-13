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
		LOG("bla");
		ImGui::ImageButton((void*)textureData.second->GetID(), ImVec2(32, 32), ImVec2(0, 0), ImVec2(32.0f, 32.0f), 2, ImColor(0, 0, 0, 255));
	}

	ImGui::End();
}
