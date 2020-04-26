#pragma once

#include <functional>
#include "Graphics/Window.h"

namespace Asylum {

	class Input
	{
	public:
		inline static bool IsKeyPressed(int keycode)
		{
			GLFWwindow* window = Window::Get()->GetNativeWindow();
			int state = glfwGetKey(window, keycode);
			return state == GLFW_PRESS || state == GLFW_REPEAT;
		}

		inline static bool IsMouseButtonPressed(int button)
		{
			GLFWwindow* window = Window::Get()->GetNativeWindow();
			int state = glfwGetMouseButton(window, button);
			return state == GLFW_PRESS;
		}

		inline static std::pair<float, float> GetMousePosition()
		{
			GLFWwindow* window = Window::Get()->GetNativeWindow();
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			return { (float)xpos, (float)ypos };
		}

		inline static float GetMouseX()
		{
			auto position = GetMousePosition();
			return position.first;
		}

		inline static float GetMouseY()
		{
			auto position = GetMousePosition();
			return position.second;
		}

		/*
		Add a function to be called whenever a key is being pressed.
		Callback function layout:
		void OnKeyPressed(int keycode)
		{
			// do something
		}
		*/
		inline static void AddKeyPressedCallback(std::function<void(int)> callback)
		{
			auto window = Window::Get();
			window->AddKeyPressedCallback(callback);
		}

		/*
		Add a function to be called whenever the mouse scroll wheel is being used.
		Callback function layout:
		void OnMouseScroll(float xoffset, float yoffset)
		{
			// do something
		}
		*/
		inline static void AddScrollCallback(std::function<void(float, float)> callback)
		{
			auto window = Window::Get();
			window->AddScrollCallback(callback);
		}

	};

}