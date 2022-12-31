#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() 
{

	glfwInit(); // initialize glfw

	// setting window options
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create window object
	GLFWwindow* window = glfwCreateWindow(1280, 720, "LearnOpenGL", glfwGetPrimaryMonitor(), NULL);

	if (window == NULL) 
	{
		std::cout << "Window creation failed." << std::endl;
		glfwTerminate();
		return -1;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	delete window;
	return 0;
}