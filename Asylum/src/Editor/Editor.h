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
	private:
		static void RenderEntityListWindow();
	};
#else
	class Editor
	{
	public:
		static void BeginCustomRender(Scope<OrthographicCameraController>& cameraController) {};
		static void EndCustomRender() {};

		static void SetEditorIsActive(bool isActive) {};
	};
#endif

}