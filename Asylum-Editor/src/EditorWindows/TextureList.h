#pragma once

#include <Asylum.h>

#include "EditorWindows/EditorWindow.h"

class TextureList : public EditorWindow
{
private:
	Asylum::Ref<Asylum::Texture> mCurrentlySelectedTexture;
public:
	TextureList();

	virtual void OnUpdate(float dt) override;
};