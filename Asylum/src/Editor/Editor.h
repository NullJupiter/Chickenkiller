#pragma once

#include <glm/glm.hpp>

#include "Graphics/OrthographicCameraController.h"

namespace Asylum {

#ifdef AM_DEBUG
	class Editor
	{
	public:
		static void BeginCustomRender(Scope<OrthographicCameraController>& cameraController);
		static void EndCustomRender();

		static void SetEditorIsActive(bool isActive);
		static bool GetIsGameWindowActive();
	private:
		static void RenderMainMenu();
		static void RenderEntityListWindow();
	};
#else
	class Editor
	{
	public:
		static void BeginCustomRender(Scope<OrthographicCameraController>& cameraController) {};
		static void EndCustomRender() {};

		static void SetEditorIsActive(bool isActive) {};
		static bool GetIsGameWindowActive() { return true; };
	};
#endif

}