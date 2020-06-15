#include "EntityList.h"

#include <imgui.h>

EntityList::EntityList()
{
	mCurrentlySelectedEntityData = nullptr;
}

void EntityList::OnUpdate(float dt)
{
	ImGui::Begin("Entity List");

	if (ImGui::TreeNodeEx("Scene"))
	{
		std::vector<Asylum::EntityData>& entityData = Asylum::EntitySystem::GetAllEntityData();
		for (uint32_t i = 0; i < entityData.size(); i++)
		{
			if (ImGui::TreeNodeEx(entityData[i].EntityName.c_str(), ImGuiTreeNodeFlags_Bullet))
			{
				if (mCurrentlySelectedEntityData == nullptr || mCurrentlySelectedEntityData->EntityID != entityData[i].EntityID)
				{
					LOG(entityData[i].EntityName);
					mCurrentlySelectedEntityData = &entityData[i];
				}
				ImGui::TreePop();
			}
		}
		ImGui::TreePop();
	}

	ImGui::End();
}
