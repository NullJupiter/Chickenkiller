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

			// event callbacks
			std::vector<std::function<void(float, float)>> ScrollCallbacks;
			std::vector<std::function<void(int)>> KeyPressedCallbacks;
			std::vector<std::function<void(int, int)>> WindowResizeCallbacks;
		};

		WindowData mData;
	public:
		static Window* Get();

		void Init(const WindowProps& props);
		void Shutdown();

		void OnUpdate();
		void SetClearColor(float r, float g, float b) const;
		void Clear() const;

		inline void AddScrollCallback(const std::function<void(float, float)>& callback) { mData.ScrollCallbacks.push_back(callback); };
		inline void AddKeyPressedCallback(const std::function<void(int)>& callback) { mData.KeyPressedCallbacks.push_back(callback); };
		inline void AddWindowResizeCallback(const std::function<void(int, int)>& callback) { mData.WindowResizeCallbacks.push_back(callback); };

		inline void RemoveAllScrollCallback() { mData.ScrollCallbacks.clear(); };
		inline void RemoveAllKeyPressedCallback() { mData.KeyPressedCallbacks.clear(); };
		inline void RemoveAllWindowResizeCallback() { mData.WindowResizeCallbacks.clear(); };

		inline uint32_t GetWidth() const { return mData.Width; };
		inline uint32_t GetHeight() const { return mData.Height; };

		inline bool IsClosed() const { return mData.IsClosed; };
		void Close() { glfwSetWindowShouldClose(mWindow, true); mData.IsClosed = true; };

		void SetVSync(bool enabled);
		inline bool IsVSync() const { return mData.VSync; };

		inline GLFWwindow* GetNativeWindow() { return mWindow; };

		inline void SetWindowTitle(const std::string& title) { glfwSetWindowTitle(mWindow, title.c_str()); };
		inline void SetWindowSize(uint32_t width, uint32_t height) { glfwSetWindowSize(mWindow, (int)width, (int)height); };
		void SetFullscreenMode();
		void SetWindowedMode(uint32_t xpos, uint32_t ypos, uint32_t width, uint32_t height);

	private:
		Window() : mWindow(nullptr) {};
		~Window() = default;
	};

}
