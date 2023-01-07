#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include <string>

// basic vector struct for storing x, y, and z values
struct basicVector3
{
	float x, y, z;
};

// just to make doing these exercises easier, returning a struct of all our object ids from each exercise
struct objectIds 
{
	unsigned int vao1, vao2, vbo1, vbo2, ebo;
};

struct shaderIds
{
	unsigned int program1, program2, program3;
};

// General Shape Draws
objectIds rainbowPentagon();
objectIds drawTriangle();

// Vertex Array & Buffer Exercises
objectIds exercise1();
objectIds exercise2();
objectIds exercise3();

// Shader & Uniform Exercises

void allErrorsFound() 
{
	GLenum current_error = glGetError();
	while (current_error)
	{
		std::cout << "Error (" << current_error << ") found." << std::endl;
		current_error = glGetError();
	}
}


void errorCheck(int success, unsigned int shader_obj, char* infoLog) 
{
	if (!success)
	{
		glGetShaderInfoLog(shader_obj, 512, NULL, infoLog);
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
	GLFWwindow* window = glfwCreateWindow(PROJECT_LENGTH, PROJECT_HEIGHT, "LearnOpenGL", NULL, NULL);

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

	Shader upsideDownShader("resources/shaders/vertex/UpsideDown.shader", "resources/shaders/fragment/ColorUniform.shader");
	const float RGB_CEIL = 255;

	//objectIds ids = rainbowPentagon();
	//objectIds ids = exercise3();
	objectIds ids = drawTriangle();
	std::cout << "Buffer stuff dealt with" << std::endl;

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // enable wireframe mode
	glEnable(GL_CULL_FACE); 
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	
	// the above settings are associated with our currently bound vertex buffer object
	std::cout << "about to enter the rendering loop" << std::endl;

	float offset = 0.0f;
	float add = 0.01;

	// the render loop
	while (!glfwWindowShouldClose(window)) // checks if the window has been 'told' to close
	{
		processInput(window); // handle user input

		// RENDER COMMANDS ...
		glClearColor(0x2D / RGB_CEIL, 0x19 / RGB_CEIL, 0x32 / RGB_CEIL, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//glUseProgram(shaderProgram);

		// DRAW PENTAGON 
		//glBindVertexArray(ids.vao);
		//glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		// DRAW PENTAGON, ORIGINAL
		/*glBindVertexArray(vertexArrayObj);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);*/

		// EXERCISE ONE
		//glBindVertexArray(ids.vao1);
		//glDrawArrays(GL_TRIANGLES, 0, 6);

		// EXERCISE TWO
		//glBindVertexArray(ids.vao1);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glBindVertexArray(ids.vao2);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		// EXERCISE THREE
		/*glUseProgram(redProgram);
		glBindVertexArray(ids.vao1);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(yellowProgram);
		glBindVertexArray(ids.vao2);
		glDrawArrays(GL_TRIANGLES, 0, 3);*/

		// Flip triangle upside down exercise
		upsideDownShader.useShader();
		upsideDownShader.setUniform1f("offset", offset);
		upsideDownShader.setUniform4f("aColor", 1.0f, 0.0f, 0.0f, 1.0f);
		glBindVertexArray(ids.vao1);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		offset += add;
		if (offset == 1.0f || offset == -1.0f) add *= -1;

		glfwSwapBuffers(window);
		glfwPollEvents(); // checks if an event has been triggered (i.e. keyboard input)
		allErrorsFound(); // errors found during each iteration
	}

	// deleting to avoid memory leaks
	glDeleteVertexArrays(2, &ids.vao1);
	glDeleteBuffers(3, &ids.vbo1);


	glfwTerminate(); // clean all of glfw's allocated resources
	return 0;
}

objectIds rainbowPentagon() 
{
	std::cout << "PLAYGROUND: Creating a rainbow colored pentagon" << std::endl;

	basicVector3 top = { 0.0f, 0.7f, 0.0f };
	basicVector3 mLeft = { -0.5f, 0.145f, 0.0f };
	basicVector3 bLeft = { -0.25f, -0.5f, 0.0f };
	basicVector3 bRight = { 0.25f, -0.5f, 0.0f };
	basicVector3 mRight = { 0.5f, 0.145f, 0.0f };

	// RGB - red, green, blue
	basicVector3 red = { 1.0f, 0.0f, 0.0f };
	basicVector3 green = { 0.0f, 1.0f, 0.0f };
	basicVector3 blue = { 0.0f, 0.0f, 1.0f };

	// testing the use of a vector struct instead of just a raw array
	// drawing a pentagon
	basicVector3 s_vertices[] = {
		top,
		mLeft,
		bLeft,
		bRight,
		mRight
	};

	basicVector3 colors[] = {
		red, green, blue,
		red, green
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,
		0, 3, 4
	};


	unsigned int vertexArrayObj, vbo_points, vbo_colors, elementBufferObj;
	glGenVertexArrays(1, &vertexArrayObj); // vertex array object creation
	glGenBuffers(1, &vbo_points); // object creation, store id in our unsigned int
	glGenBuffers(1, &elementBufferObj);
	glGenBuffers(1, &vbo_colors);

	glBindVertexArray(vertexArrayObj); // we bind our vertex array prior to binding any vertex buffers

	// bind all our buffers
	// point buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo_points);
	glBufferData(GL_ARRAY_BUFFER, sizeof(s_vertices), s_vertices, GL_STATIC_DRAW);
	// index buffer (elements)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObj);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// colors buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	// specify how our vertex data should be interpreted
	glBindBuffer(GL_ARRAY_BUFFER, vbo_points);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);

	// enable vertex buffers at index 0 and index 1
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// unbind all
	glBindVertexArray(0); // be sure to unbind the vertex array first (to preserve all bound states)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return { vertexArrayObj, 0, vbo_points, vbo_colors, elementBufferObj };
}

// draw two triangles right next to each other
objectIds exercise1() 
{
	std::cout << "EXERCISE ONE: Create two different triangles using one vertexbuffer" << std::endl;

	basicVector3 red = { 1.0f, 0.0f, 0.0f }; // red
	basicVector3 green = { 0.0f, 1.0f, 0.0f };

	basicVector3 points[] = {
		{-0.5f, 0.0f, 0.0f}, // left triangle top
		{-0.75f, -0.5f, 0.0f}, // left triangle left
		{-0.25f, -0.5f, 0.0f}, // left triangle right
		{0.5f, 0.5f, 0.0f}, // right triangle top
		{0.25f, 0.0f, 0.0f}, // right triangle left
		{0.75, 0.0f, 0.0f}, // right triangle right
	};

	basicVector3 colors[] = {
		red, red, red, // triangle 1
		green, green, green // triangle 2
	};

	unsigned int vao, vbo_points, vbo_colors;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo_points);
	glGenBuffers(1, &vbo_colors);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_points);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, sizeof(basicVector3), NULL);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(basicVector3), NULL);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return {vao, 0, vbo_points, vbo_colors, 0};
}

objectIds exercise2() 
{
	std::cout << "EXERCISE TWO: Create two triangles using two seperate vertex arrays (and buffers)" << std::endl;

	basicVector3 red = { 1.0f, 0.0f, 0.0f };
	basicVector3 green = { 0.0f, 1.0f, 0.0f };
	basicVector3 blue = { 0.0f, 0.0f, 1.0f };

	basicVector3 points1[] = {
		{-0.5f, 0.0f, 0.0f}, // left triangle top
		{-0.75f, -0.5f, 0.0f}, // left triangle left
		{-0.25f, -0.5f, 0.0f} // left triangle right
	};

	basicVector3 points2[] = {
		{0.5f, 0.5f, 0.0f}, // right triangle top
		{0.25f, 0.0f, 0.0f}, // right triangle left
		{0.75, 0.0f, 0.0f} // right triangle right
	};

	basicVector3 colors[] = {
		red, green, blue
	};

	unsigned int VBOS[3], VAOS[2];
	// left vaos[0] be the left triangle, vaos[1] be the right
	// vbos[2] is our left tri vertex buffer, vbos[3] right buffer
	glGenVertexArrays(2, VAOS); // generate vertex arrays in the array
	glGenBuffers(3, VBOS); // generate vertex buffers in the array

	glBindVertexArray(VAOS[0]); // left triangle
	glBindBuffer(GL_ARRAY_BUFFER, VBOS[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points1), points1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(basicVector3), NULL);

	glBindBuffer(GL_ARRAY_BUFFER, VBOS[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(basicVector3), NULL);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(VAOS[1]); // right triangle
	glBindBuffer(GL_ARRAY_BUFFER, VBOS[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points2), points2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(basicVector3), NULL);

	glBindBuffer(GL_ARRAY_BUFFER, VBOS[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(basicVector3), NULL);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return { VAOS[0], VAOS[1], VBOS[0], VBOS[1], VBOS[2]};
}

objectIds exercise3() 
{
	std::cout << "EXERCISE THREE: Draw both triangles again but each program uses a different fragment shader" << std::endl;

	basicVector3 points1[] = {
		{-0.5f, 0.0f, 0.0f}, // left triangle top
		{-0.75f, -0.5f, 0.0f}, // left triangle left
		{-0.25f, -0.5f, 0.0f} // left triangle right
	};

	basicVector3 points2[] = {
		{0.5f, 0.5f, 0.0f}, // right triangle top
		{0.25f, 0.0f, 0.0f}, // right triangle left
		{0.75, 0.0f, 0.0f} // right triangle right
	};

	unsigned int vaos[2], vbos[2];
	glGenVertexArrays(2, vaos);
	glGenBuffers(2, vbos);
	
	// left triangle
	glBindVertexArray(vaos[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points1), points1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(basicVector3), NULL);
	glEnableVertexAttribArray(0);

	// right triangle
	glBindVertexArray(vaos[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points2), points2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(basicVector3), NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return {vaos[0], vaos[1], vbos[0], vbos[1], 0};
}

objectIds drawTriangle()
{
	basicVector3 vertices[] = {
		{0.0f, 0.5f, 0.0f},
		{0.5f, 0.0f, 0.0f},
		{-0.5f, 0.0f, 0.0f}
	};

	unsigned int vao, vbo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(basicVector3), NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	allErrorsFound();

	return { vao, 0, vbo, 0, 0 };
}