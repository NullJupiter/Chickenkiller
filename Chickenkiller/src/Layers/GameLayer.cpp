#include "GameLayer.h"

#include "App.h"

// include all entities
#include "Entities/Player.h"
#include "Entities/Enemy.h"

GameLayer::GameLayer()
{
	
}

void GameLayer::OnAttach()
{
	LOG("[*] Game Layer Attached!");
	
	// create camera controller
	mCameraController = std::make_unique<Asylum::OrthographicCameraController>(16.0f / 9.0f, true);

	// register all entities
	Asylum::EntitySystem::RegisterEntity(Asylum::EntityData("Player", std::make_shared<Player>(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)), "default"));
	Asylum::EntitySystem::RegisterEntity(Asylum::EntityData("Enemy", std::make_shared<Enemy>(glm::vec2(2.0f, 0.0f), glm::vec2(1.0f, 1.0f)), "default"));

	Asylum::Input::AddKeyPressedCallback([this](int keycode)
		{
			if (keycode == AM_KEY_F1)
			{
				Asylum::EntitySystem::SetEntityShader("Player", Asylum::ResourceManager::GetShader("red"));
			}
			else if (keycode == AM_KEY_F2)
			{
				Asylum::EntitySystem::SetEntityShader("Player", Asylum::ResourceManager::GetShader("default"));
			}
		});
}

void GameLayer::OnUpdate(float dt)
{
	// updating
	{
		// update the camera controller
		mCameraController->OnUpdate(dt);

		// update all entities
		Asylum::EntitySystem::OnUpdate(dt);
	}

	// rendering
	{
		// render all entities
		Asylum::EntitySystem::OnRender(mCameraController);
	}
}

void GameLayer::OnDetach()
{
	LOG("[*] Game Layer Detached!");
}
