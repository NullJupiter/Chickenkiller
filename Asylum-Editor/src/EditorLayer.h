#pragma once

#include <Asylum.h>

#include "EditorWindows/MainMenu.h"
#include "EditorWindows/Viewport.h"
#include "EditorWindows/EntityList.h"

class EditorLayer : public Asylum::Layer
{
private:
	// editor windows
	Asylum::Scope<MainMenu> mMainMenuWindow;
	Asylum::Scope<Viewport> mViewportWindow;
	Asylum::Scope<EntityList> mEntityListWindow;
public:
	EditorLayer();

	virtual void OnUpdate(float dt) override;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
private:
	virtual void AddEventCallbacks() override;

	void CreateDockSpace();
};