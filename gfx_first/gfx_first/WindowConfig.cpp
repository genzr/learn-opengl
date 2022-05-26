#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <WindowConfig.h>

WindowConfig::WindowConfig() {
	// Initializing GLFW
	// GLFW will provide an OpenGL context for us to operate in.
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Use this for MAC OS X

	// Creating a window
	setWindow(glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL));
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

}