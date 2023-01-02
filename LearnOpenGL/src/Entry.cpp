#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void processInput(GLFWwindow* window) 
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
		std::cout << "Window was closed using escape key" << std::endl;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main() 
{

	glfwInit(); // initialize glfw

	// setting window options
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	const int PROJECT_LENGTH = 1280;
	const int PROJECT_HEIGHT = 720;

	// create window object
	GLFWwindow *window = glfwCreateWindow(PROJECT_LENGTH, PROJECT_HEIGHT, "LearnOpenGL", NULL, NULL);

	// check for proper window creation
	if (window == NULL) 
	{
		std::cout << "Window creation failed." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// check for proper GLAD initialization
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, PROJECT_LENGTH, PROJECT_HEIGHT); // indicate rendering window size
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	const float RGB_CEIL = 255;
	// the render loop
	while (!glfwWindowShouldClose(window)) // checks if the window has been 'told' to close
	{
		processInput(window); // handle user input

		// RENDER COMMANDS ...
		glClearColor(0xFF / RGB_CEIL, 0xC0 / RGB_CEIL, 0xCB / RGB_CEIL, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents(); // checks if an event has been triggered (i.e. keyboard input)
	}

	glfwTerminate(); // clean all of glfw's allocated resources
	return 0;
}