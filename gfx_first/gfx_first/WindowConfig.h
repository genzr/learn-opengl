#pragma once
#include <glad/glad.h>
#include <glfw3.h>

class WindowConfig
{
	private:
		GLFWwindow* window = NULL;

	public:
		WindowConfig();
		GLFWwindow* getWindow() { return window; }
		void setWindow(GLFWwindow* w) { window = w; }
};

