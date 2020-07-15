#pragma once

#include <Asylum.h>

#include "EditorWindows/EditorWindow.h"

class ResourceTree : public EditorWindow
{
public:
	ResourceTree();

	virtual void OnUpdate(float dt) override;
};