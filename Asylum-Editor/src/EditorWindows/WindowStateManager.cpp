#include "WindowStateManager.h"

struct WindowStateManagerData
{
	bool IsGridOn = false;

	Asylum::Ref<Asylum::Texture> CurrentlySelectedTexture = nullptr;
};
static WindowStateManagerData sData;

void WindowStateManager::Init()
{
	sData.CurrentlySelectedTexture = Asylum::ResourceManager::GetTexture("unknown");
}

void WindowStateManager::SetSelectedTexture(const Asylum::Ref<Asylum::Texture>& currentlySelectedTexture)
{
	if (sData.CurrentlySelectedTexture != currentlySelectedTexture)
		sData.CurrentlySelectedTexture = currentlySelectedTexture;
}

const Asylum::Ref<Asylum::Texture>& WindowStateManager::GetSelectedTexture()
{
	return sData.CurrentlySelectedTexture;
}

bool WindowStateManager::IsGridOn()
{
	return sData.IsGridOn;
}

void WindowStateManager::IsGridOn(bool newGridState)
{
	sData.IsGridOn = newGridState;
}
