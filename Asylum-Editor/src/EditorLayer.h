#pragma once

#include <Asylum.h>

#include "EditorWindows/Viewport.h"

class EditorLayer : public Asylum::Layer
{
private:
	// editor windows
	Asylum::Scope<Viewport> mViewportWindow;
public:
	EditorLayer();

	virtual void OnUpdate(float dt) override;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
private:
	virtual void AddEventCallbacks() override;

	void CreateDockSpace();
};