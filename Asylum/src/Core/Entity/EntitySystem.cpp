#include "ampch.h"
#include "EntitySystem.h"

#include "Graphics/Renderer.h"

namespace Asylum {

	struct EntitySystemData
	{
		std::vector<EntityData> EntitiesData;
		std::vector<std::pair<std::shared_ptr<Shader>, std::vector<uint32_t>>> ShaderEntityDataMap;
	};
	static EntitySystemData sData;

	// Do not call this method before initialising the resource manager!
	void EntitySystem::Init()
	{
		// get all loaded shaders
		std::vector<std::shared_ptr<Shader>> allShaders = ResourceManager::GetAllShaders();

		// initialize shader entity data map with all loaded shaders
		sData.ShaderEntityDataMap.reserve(allShaders.size());
		for (std::shared_ptr<Shader> shader : allShaders)
			sData.ShaderEntityDataMap.push_back(std::make_pair(shader, std::vector<uint32_t>()));
	}

	void EntitySystem::RegisterEntity(EntityData entityData)
	{
		// push back the entity data and get the entity data index in vector
		sData.EntitiesData.push_back(entityData);

		for (auto& shaderEntityDataEntry : sData.ShaderEntityDataMap)
		{
			// if the entity shader is the stored shader push back the entity index
			if (shaderEntityDataEntry.first == entityData.CurrentEntityShader)
				shaderEntityDataEntry.second.push_back(entityData.EntityID);
		}
	}

	void EntitySystem::SetEntityShader(const std::string& entityName, std::shared_ptr<Shader> shader)
	{
		EntityData* data = nullptr;

		// find entity data
		for (auto& entityData : sData.EntitiesData)
		{
			if (entityData.EntityName == entityName)
			{
				// change entity shader
				entityData.CurrentEntityShader = shader;

				data = &entityData;

				break;
			}
		}

		// erase entity id from old shader-entity data map
		if (data != nullptr)
		{
			// find entity id in shader-entity data map
			for (auto& shaderEntityData : sData.ShaderEntityDataMap)
			{
				std::vector<uint32_t>& entityIDList = shaderEntityData.second;
				for (uint32_t i = 0; i < entityIDList.size(); i++)
				{
					if (data->EntityID == entityIDList[i])
					{
						entityIDList.erase(entityIDList.begin()+i);
					}
				}
			}
		}

		for (auto& shaderEntityDataEntry : sData.ShaderEntityDataMap)
		{
			// if the entity shader is the stored shader push back the entity index
			if (shaderEntityDataEntry.first == shader)
				shaderEntityDataEntry.second.push_back(data->EntityID);
		}

	}

	void EntitySystem::OnUpdate(float dt)
	{
		// update all registered entities
		for (auto& entityData : sData.EntitiesData)
		{
			// if the entity is active update
			if (entityData.EntityObject->IsActive())
				entityData.EntityObject->OnUpdate(dt);
		}
	}

	void EntitySystem::OnRender(std::unique_ptr<OrthographicCameraController>& cameraController)
	{
		for (auto& shaderEntityDataEntry : sData.ShaderEntityDataMap)
		{
			std::shared_ptr<Shader> currentShader = shaderEntityDataEntry.first;
			const std::vector<uint32_t>& entityIDs = shaderEntityDataEntry.second;

			// bind shader
			currentShader->Bind();

			// set view projection matrix for shader
			currentShader->SetUniformMat4("uViewProjection", cameraController->GetCamera().GetViewProjectionMatrix());

			Renderer::BeginDraw();
			for (auto& entityID : entityIDs)
			{
				for (auto& entityData : sData.EntitiesData)
				{
					if (entityData.EntityID == entityID)
					{
						const EntityData& currentEntityData = entityData;
						if (currentEntityData.EntityObject->IsActive())
							currentEntityData.EntityObject->OnRender();
					}
				}
			}
			Renderer::EndDraw();
		}
	}


}