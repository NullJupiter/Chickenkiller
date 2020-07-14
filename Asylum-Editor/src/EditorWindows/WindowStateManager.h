#pragma once

#include <Asylum.h>

class WindowStateManager
{
public:
	static void Init();

	static void SetSelectedTexture(const Asylum::Ref<Asylum::Texture>& currentlySelectedTexture);
	static const Asylum::Ref<Asylum::Texture>& GetSelectedTexture();

	static bool IsGridOn();
	static void IsGridOn(bool newGridState);
};