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
		std::shared_ptr<Entity> EntityObject;
		std::shared_ptr<Shader> CurrentEntityShader;

		EntityData(const std::string& name, std::shared_ptr<Entity> entity, const std::string& shaderName)
			: EntityName(name), EntityObject(entity), EntityID(LastEntityID++)
		{
			CurrentEntityShader = ResourceManager::GetShader(shaderName);
		}
	};

	class EntitySystem
	{
	public:
		static void Init();
	
		static void RegisterEntity(EntityData entityData);
		static void OnUpdate(float dt);
		static void OnRender(std::unique_ptr<OrthographicCameraController>& cameraController);

		static void SetEntityShader(const std::string& entityName, std::shared_ptr<Shader> shader);
	};

}