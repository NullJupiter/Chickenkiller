#pragma once

#include "imgui.h"

class ImGuiManager
{
public:
	static void Init();
	static void Shutdown();

	static void CreateFonts(float fontSize);

	static void Begin();
	static void End();
private:
	static void SetStyle();
};