#pragma once

#include <Asylum.h>

#include "EditorWindows/EditorWindow.h"

class TextureList : public EditorWindow
{
public:
	TextureList();

	virtual void OnUpdate(float dt) override;
};