#pragma once

#include <glm/glm.hpp>

#include "Graphics/OrthographicCameraController.h"

namespace Asylum {

#ifdef AM_DEBUG
	class Editor
	{
	public:
		static void BeginCustomRender();
		static void EndCustomRender();

		static void SetEditorIsActive(bool isActive);
		static bool IsEditorActive();
		static bool IsGameWindowActive();

		static const glm::vec2& GetGameWindowSize();
	private:
		// imgui window rendering
		static void RenderMainMenu();
		static void RenderEntityListWindow();
	};
#else
	class Editor
	{
	public:
		static void BeginCustomRender() {};
		static void EndCustomRender() {};

		static void SetEditorIsActive(bool isActive) {};
		static bool IsEditorActive() { return false; };
		static bool IsGameWindowActive() { return true; };

		static const glm::vec2& GetGameWindowSize() { return { 0.0f, 0.0f }; };
	};
#endif

}