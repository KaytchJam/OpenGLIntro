#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


void errorCheck(int success, unsigned int vso, char* infoLog) 
{
	if (!success)
	{
		glGetShaderInfoLog(vso, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void processInput(GLFWwindow* window) 
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
		std::cout << "Window was closed using escape key" << std::endl;
	}
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
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

	// vertices of our triangle
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	unsigned int vertexArrayObj;
	glGenVertexArrays(1, &vertexArrayObj); // vertex array object creation
	glBindVertexArray(vertexArrayObj);

	unsigned int vertexBufferObj;
	glGenBuffers(1, &vertexBufferObj); // object creation, store id in our unsigned int
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObj);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// writing shader code
	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

	unsigned int vertexShaderObject;
	vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderObject, 1, &vertexShaderSource, NULL); // binding our shader source to our vertex object
	glCompileShader(vertexShaderObject); // compile our shader

	// check for errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShaderObject, GL_COMPILE_STATUS, &success);
	errorCheck(success, vertexShaderObject, infoLog);

	unsigned int fragmentShaderObject;
	fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderObject, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShaderObject); // compile our shader

	// create a program object that we'll link our two compiled shaders to
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShaderObject);
	glAttachShader(shaderProgram, fragmentShaderObject);
	glLinkProgram(shaderProgram); // links all our attached shaders within the program

	// check for errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	errorCheck(success, shaderProgram, infoLog);

	// finally, we use the program
	glUseProgram(shaderProgram);
	// once our shaders have been linked to the program object, we can delete them
	glDeleteShader(vertexShaderObject);
	glDeleteShader(fragmentShaderObject);

	// specify how our vertex data should be interpreted
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// the above settings are associated with our currently bound vertex buffer object

	// the render loop
	while (!glfwWindowShouldClose(window)) // checks if the window has been 'told' to close
	{
		processInput(window); // handle user input

		// RENDER COMMANDS ...
		glClearColor(0xFF / RGB_CEIL, 0x14 / RGB_CEIL, 0x93 / RGB_CEIL, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(vertexArrayObj);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents(); // checks if an event has been triggered (i.e. keyboard input)
	}

	glfwTerminate(); // clean all of glfw's allocated resources
	return 0;
}