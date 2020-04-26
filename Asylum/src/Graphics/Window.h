#pragma once

#include <string>

#include <GLFW/glfw3.h>

namespace Asylum {

	struct WindowProps {
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "Engine Title",
			uint32_t width = 1280,
			uint32_t height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

#define MAX_KEYS 1024
#define MAX_MOUSE_BUTTONS 32

	class Window
	{
	private:
		static Window* sInstance;

		GLFWwindow* mWindow;

		struct WindowData
		{
			std::string Title;
			uint32_t Width, Height = 0;
			bool VSync = true;
			bool IsClosed = false;

			std::vector<std::function<void(float, float)>> ScrollCallbacks;
			std::vector<std::function<void(int)>> KeyPressedCallbacks;
		};

		WindowData mData;
	public:
		static Window* Get();

		void Init(const WindowProps& props);
		void Shutdown();

		void OnUpdate();
		void SetClearColor(float r, float g, float b) const;
		void Clear() const;

		inline void AddScrollCallback(std::function<void(float, float)> callback) { mData.ScrollCallbacks.push_back(callback); };
		inline void AddKeyPressedCallback(std::function<void(int)> callback) { mData.KeyPressedCallbacks.push_back(callback); };

		inline uint32_t GetWidth() const { return mData.Width; };
		inline uint32_t GetHeight() const { return mData.Height; };

		inline bool IsClosed() const { return mData.IsClosed; };
		void Close() { glfwSetWindowShouldClose(mWindow, true); mData.IsClosed = true; };

		void SetVSync(bool enabled);
		inline bool IsVSync() const { return mData.VSync; };

		inline GLFWwindow* GetNativeWindow() { return mWindow; };

	private:
		Window() : mWindow(nullptr) {};
		~Window() = default;
	};

}
