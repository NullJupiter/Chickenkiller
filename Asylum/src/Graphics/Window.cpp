#include "ampch.h"
#include "Window.h"

#include "Core/Log.h" 

namespace Asylum {

	Window* Window::sInstance = nullptr;

	Window* Window::Get()
	{
		if (!sInstance) sInstance = new Window();
		return sInstance;
	}


	static void GLFWErrorCallback(int error, const char* description)
	{
		LOG("GLFW Error Code: " << error);
		LOG("GLFW Error Description: " << description);
	}

	void Window::Init(const WindowProps& props)
	{
		mData.Title = props.Title;
		mData.Width = props.Width;
		mData.Height = props.Height;

		LOG("Creating window: " << mData.Title << ". (" << mData.Width << ", " << mData.Height << ")");

		// initialize glfw
		glfwInit();
		glfwSetErrorCallback(GLFWErrorCallback);

		// set glfw options
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef PLATFORM_DARWIN
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

		// create window
		mWindow = glfwCreateWindow((int)mData.Width, (int)mData.Height, mData.Title.c_str(), nullptr, nullptr);

		// set context
		glfwMakeContextCurrent(mWindow);

		// initialize glad
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			LOG("Could not initialize glad!");

		// set viewport
		glfwGetFramebufferSize(mWindow, (int*)&mData.Width, (int*)&mData.Height);
		glViewport(0, 0, mData.Width, mData.Height);

		// log information
		LOG("OpenGL Info:");
		LOG("  Vendor: " << glGetString(GL_VENDOR));
		LOG("  Renderer: " << glGetString(GL_RENDERER));
		LOG("  Version: " << glGetString(GL_VERSION));

		glfwSetWindowUserPointer(mWindow, &mData);
		SetVSync(true);

		// enable blending
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

		// enable face culling
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;
			});

		glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.IsClosed = true;
			});

		glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				if (action == GLFW_PRESS || action == GLFW_REPEAT)
				{
					for (auto& fn : data.KeyPressedCallbacks)
						fn(key);
				}
			});

		glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				for (auto& fn : data.ScrollCallbacks)
					fn((float)xoffset, (float)yoffset);
			});
	}

	void Window::Shutdown()
	{
		glfwDestroyWindow(mWindow);
		glfwTerminate();

		delete sInstance;
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(mWindow);
	}

	void Window::SetClearColor(float r, float g, float b) const
	{
		glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
	}

	void Window::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::SetVSync(bool enabled)
	{
		mData.VSync = enabled;
		glfwSwapInterval(enabled);
	}

}