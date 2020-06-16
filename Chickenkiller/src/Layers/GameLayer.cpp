#include "GameLayer.h"

// include all entities
#include "Entities/Player.h"
#include "Entities/Enemy.h"

GameLayer::GameLayer()
{
	
}

void GameLayer::OnAttach()
{
	LOG("[*] Game Layer Attached!");

	// register all entities (in draw order)
	Asylum::EntitySystem::RegisterEntity(Asylum::EntityData("Enemy", Asylum::CreateRef<Enemy>(glm::vec2(2.0f, 0.0f), glm::vec2(1.0f, 1.0f)), "default"));
	Asylum::EntitySystem::RegisterEntity(Asylum::EntityData("Player", Asylum::CreateRef<Player>(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)), "default"));
}

void GameLayer::AddEventCallbacks()
{
	Asylum::Input::AddKeyPressedCallback(AM_BIND_FN_1(GameLayer::OnKeyPressed));
}

void GameLayer::OnUpdate(float dt)
{
	// updating
	{
		// update all entities
		Asylum::EntitySystem::OnUpdate(dt);
	}

	// rendering
	{		
		// render all entities
		Asylum::EntitySystem::OnRender();
	}
}

void GameLayer::OnDetach()
{
	LOG("[*] Game Layer Detached!");

	// remove all entities
	Asylum::EntitySystem::RemoveAllEntities();
}

void GameLayer::OnKeyPressed(int keycode)
{

}
