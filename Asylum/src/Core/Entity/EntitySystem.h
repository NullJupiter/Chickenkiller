#pragma once

#include "Core/Entity/Entity.h"
#include "Graphics/Shader.h"
#include "Graphics/OrthographicCameraController.h"
#include "Core/ResourceManager.h"

namespace Asylum {

	static uint32_t LastEntityID = 0;

	struct EntityData
	{
		uint32_t EntityID;
		std::string EntityName;
		Ref<Entity> EntityObject;
		Ref<Shader> CurrentEntityShader;

		EntityData() {}
		EntityData(const std::string& name, Ref<Entity> entity, const std::string& shaderName)
			: EntityName(name), EntityObject(entity), EntityID(LastEntityID++)
		{
			CurrentEntityShader = ResourceManager::GetShader(shaderName);
		}
	};

	class EntitySystem
	{
	public:
		static void Init();
		static void RemoveAllEntities();
	
		static void RegisterEntity(EntityData entityData);
		static void OnUpdate(float dt);
		static void OnRender();

		static const std::vector<EntityData>& GetAllEntityData();
		static const EntityData& GetEntityData(std::string name);
		static void SetEntityShader(const std::string& entityName, const Ref<Shader>& shader);
	};

}