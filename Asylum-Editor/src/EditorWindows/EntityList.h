#pragma once

#include <Asylum.h>

#include "EditorWindows/EditorWindow.h"

class EntityList : public EditorWindow
{
private:
	Asylum::EntityData* mCurrentlySelectedEntityData;
public:
	EntityList();

	virtual void OnUpdate(float dt) override;
};