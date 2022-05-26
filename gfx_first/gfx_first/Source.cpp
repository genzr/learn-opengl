#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <WindowConfig.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main() {

	// Initialize Window
	GLFWwindow* window = WindowConfig().getWindow();

	// Making the created window the current context
	glfwMakeContextCurrent(window);

	//Initializing GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return 1;
	}

	// Setting the OpenGL viewport
	glViewport(0, 0, 800, 600);

	// We are setting a callback to update the viewport when the window is resized.
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	// Setup Vertex Shader sources
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	// Setup fragment shader sources
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);}\0";

	const char* fragmentShaderSourceYellow = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);}\0";



	// Creating a Vertex Shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	// Checking if shader compilation was successful
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << infoLog << std::endl;
	}

	// Creating fragment shaders
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << infoLog << std::endl;
	}

	unsigned int fragmentShaderYellow;
	fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSourceYellow, NULL);
	glCompileShader(fragmentShaderYellow);

	glGetShaderiv(fragmentShaderYellow, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShaderYellow, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << infoLog << std::endl;
	}





	// Create a Shader Program 
	// link our Vertex and Fragment shaders to the program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	unsigned int shaderProgramYellow;
	shaderProgramYellow = glCreateProgram();
	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
	glLinkProgram(shaderProgramYellow);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED" << infoLog << std::endl;
	}

	// Remove shaders as they have already been linked to the program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Vertex input
	float vertices[] = {
		-1.0f, 0.0f, 0.0f,
		-0.5f, 1.f, 0.0f,
		-0.0f, -0.0f, 0.0f,
	};

	float verticesTwo[] = {
		0.0f, 0.0f, 0.0f,
		0.5f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
	};
	
	//Initialising VAOs and VOBs
	unsigned int VAOs[2], VBOs[2];
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);


	// Binding VAOs and VBOs to the GPU
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Binding 2nd VAOs and VBOs to the GPU
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTwo), verticesTwo, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Turn on wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window))
	{

		// input
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);

		// draw first triangle
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgramYellow);

		// draw second triangle
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

}