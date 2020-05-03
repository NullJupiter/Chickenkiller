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
	mCameraController = Asylum::CreateScope<Asylum::OrthographicCameraController>(16.0f / 9.0f, true);

	// register all entities (in draw order)
	Asylum::EntitySystem::RegisterEntity(Asylum::EntityData("Enemy", Asylum::CreateRef<Enemy>(glm::vec2(2.0f, 0.0f), glm::vec2(1.0f, 1.0f)), "default"));
	Asylum::EntitySystem::RegisterEntity(Asylum::EntityData("Player", Asylum::CreateRef<Player>(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f)), "default"));

	Asylum::Input::AddKeyPressedCallback(AM_BIND_FN_1(GameLayer::OnKeyPressed));
}

void GameLayer::OnUpdate(float dt)
{
	// updating
	{
		if (Asylum::Editor::GetIsGameWindowActive())
		{
			// update the camera controller
			mCameraController->OnUpdate(dt);

			// update all entities
			Asylum::EntitySystem::OnUpdate(dt);
		}
	}

	// rendering
	{
		Asylum::Editor::BeginCustomRender(mCameraController);
		
		// render all entities
		Asylum::EntitySystem::OnRender(mCameraController);

		Asylum::Editor::EndCustomRender();
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
	if (keycode == AM_KEY_F1)
	{
		Asylum::Editor::SetEditorIsActive(false);
		mCameraController->UpdateProjection(16.0f / 9.0f);
	}
	else if (keycode == AM_KEY_F2)
	{
		Asylum::Editor::SetEditorIsActive(true);
	}
}
