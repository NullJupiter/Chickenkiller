#pragma once

#include <Asylum.h>

#include "EditorWindows/EditorWindow.h"

class MainMenu : public EditorWindow
{
private:
public:
	MainMenu();

	virtual void OnUpdate(float dt) override;
};