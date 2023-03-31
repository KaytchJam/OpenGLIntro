#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// IMAGE / TEXTURE FUNCTIONALITY
#include "vendor/stb_image/stb_image.h"

// My additions
#include "gl_tools/Shader.h"
#include "gl_tools/ErrorHandler.h"
#include "Canvas2D.h"

// C/C++ Standard Library
#include <string>
#include <math.h>
#include <time.h>
#include <cmath>

// GLM MATRIX MATH
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int TARGET_FPS = 30;
const float RGB_CEIL = 255;


// basic vector struct for storing x, y, and z values
struct basicVector3 { float x, y, z; };
struct basicVector2 { float x, y; };
struct intVector2 { int x, y; };


// just to make doing these exercises easier, returning a struct of all our object ids from each exercise
struct objectIds { unsigned int vao1, vao2, vbo1, vbo2, ebo; };
struct extendedObjectIds { unsigned int vao1, vao2, vbo1, vbo2, ebo1, ebo2, txt1, txt2; };
struct shaderIds { unsigned int program1, program2, program3; };

struct plane_object {
	float y;
	struct extendedObjectIds data;
};

basicVector2 addVector(basicVector2 v1, basicVector2 v2) { return { v1.x + v2.x, v1.y + v2.y }; }
basicVector2 scalarVector(float scalar, basicVector2 v1) { return { scalar * v1.x, scalar * v1.y }; }

// General Shape Draws
objectIds rainbowPentagon();
extendedObjectIds drawTriangle(float r, float g, float b);
extendedObjectIds textureSquare(std::string img_path, std::string img_path_2);
extendedObjectIds drawDroplet(std::string img_path);
extendedObjectIds drawPlane(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4);
extendedObjectIds drawPrism(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, float height);
extendedObjectIds *drawMatrixPrisms(int* mat, unsigned int MAT_SIZE);

// Vertex Array & Buffer Exercises
objectIds exercise1();
objectIds exercise2();
objectIds exercise3();

// Messing Around / Testing
extendedObjectIds bouncingLogo(std::string logo_path);

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

void printMat4(glm::mat4& myMat) 
{
	std::printf("%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n",
		myMat[0].x, myMat[1].x, myMat[2].x, myMat[3].x,
		myMat[0].y, myMat[1].y, myMat[2].y, myMat[3].y,
		myMat[0].z, myMat[1].z, myMat[2].z, myMat[3].z,
		myMat[0].w, myMat[1].w, myMat[2].w, myMat[3].w);
	std::cout << std::endl;
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

	//std::string shaderPath("resources/shaders/");
	Shader myShader("resources/shaders/vertex/NoTexTransform.shader", "resources/shaders/fragment/ColorUniform.shader");
	Canvas2D canva(100, 100, & myShader);

	Rect2D r1 = Rect2D(0, 0, 20, 20);
	r1.translate(50 - (r1.getLength() / 2), 50 - (r1.getHeight() / 2));

	myShader.setUniform1i("hex_color", 0x15A477);

	std::cout << "Buffer stuff dealt with" << std::endl;

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // enable wireframe mode
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_CULL_FACE); 
	glEnable(GL_DEPTH_TEST);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);
	
	// the above settings are associated with our currently bound vertex buffer object
	std::cout << "about to enter the rendering loop" << std::endl;

	// the render loop
	double lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window)) // checks if the window has been 'told' to close
	{
		processInput(window); // handle user input

		while (glfwGetTime() < lastTime + 1.0/TARGET_FPS) {

			// RENDER COMMANDS ...
			glClearColor(0xFF / RGB_CEIL, 0xFF / RGB_CEIL, 0xFF / RGB_CEIL, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glClear(GL_DEPTH_BUFFER_BIT);

			canva.renderShape(r1);

			glfwSwapBuffers(window);
			glfwPollEvents(); // checks if an event has been triggered (i.e. keyboard input)
			allErrorsFound(); // errors found during each iteration
		}
		lastTime += 1.0 / TARGET_FPS;

	}

	/*glDeleteVertexArrays(2, &id.vao1);
	glDeleteBuffers(4, &id.vbo1);
	glDeleteTextures(2, &id.txt1);*/
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

extendedObjectIds drawTriangle(float r, float g, float b)
{
	basicVector3 vertices[] = {
		{0.0f, 0.25f, 0.0f}, // FIRST 3, TRIANGLE VERTICES
		{0.25f, 0.0f, 0.0f},
		{-0.25f, 0.0f, 0.0f},
		{r / 255, 0.0f, 0.0f},
		{0.0f, g / 255, 0.0f},
		{0.0f, 0.0f, b / 255}
	};

	unsigned int vao, vbo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(basicVector3), NULL);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(basicVector3), (void*)(3 * sizeof(basicVector3)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	allErrorsFound();

	return { vao, 0, vbo, 0, 0, 0, 0, 0};
}

extendedObjectIds textureSquare(std::string img_path, std::string img_path_2)
{

	float vertices[] = {
	// [ Positions     (3)][ Colors      (3)][ Texture Postion (2)]
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 
		0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};

	unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	// TEXTURE PART
	unsigned int texture1, texture2;
	// texture 1
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// texture wrappign params
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// texture filter params
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	// flip loaded image along axis
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(img_path.c_str(), &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// texture 2
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	
	// setting bound texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	data = stbi_load(img_path_2.c_str(), &width, &height, &nrChannels, 0);
	if (data) {
		// pngs have a transparency channel so we use rgba instead of rgb
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return { VAO, 0, VBO, 0, EBO, 0, texture1, texture2};
}

extendedObjectIds bouncingLogo(std::string logo_path)
{
	//std::cout << "Entering bouncingLogo" << std::endl;
	float vertices[] = {
		-0.25f, -0.25f, 0.0f, // positions 1
		0.0f, 0.0f, // texture coords 1

		0.25f, -0.25f, 0.0f, // positions 2
		1.0f, 0.0f, // texture coords 2

		0.25f, 0.25f, 0.0f, // positions 3
		1.0f, 1.0f, // texture coords 3

		-0.25f, 0.25f, 0.0f, // positions 4
		0.0f, 1.0f, // texture coords 4
	};

	unsigned int indices[] = {0, 1, 2, 2, 3, 0}; // square indices

	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	//std::cout << "BINDING VERTEX BUFFER" << std::endl;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//std::cout << "BINDING ELEMENT BUFFER" << std::endl;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, NULL);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//std::cout << "TEXTURE STUFFS" << std::endl;
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//std::cout << "IMAGE LOADING" << std::endl;
	stbi_set_flip_vertically_on_load(true);
	int width, height, nr_channels;
	unsigned char* img_data = stbi_load(logo_path.c_str(), &width, &height, &nr_channels, 0);
	if (img_data) {
		//std::printf("number of channels: %d", nr_channels);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	//std::cout << "FREEING IMAGE" << std::endl;
	stbi_image_free(img_data);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindTexture(GL_TEXTURE, 0);

	std::cout << "leaving bouncingLogo" << std::endl;
	return {VAO, 0, VBO, 0, EBO, 0, texture1, 0};
}

extendedObjectIds drawPlane(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4) {
	float vertices[] = {
		p1.x, p1.y, p1.z,
		p2.x, p2.y, p2.z,
		p3.x, p3.y, p3.z,
		p4.x, p4.y, p4.z
	};

	unsigned int indices[] = {
		0, 1, 2, 2, 3, 0
	};

	unsigned int vao, vbo, ebo;
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));

	GLCall(glGenBuffers(1, &vbo));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, NULL));
	GLCall(glEnableVertexAttribArray(0));

	GLCall(glGenBuffers(1, &ebo));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

	GLCall(glBindVertexArray(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

	return { vao, 0, vbo, 0, ebo, 0, 0, 0 };
}

extendedObjectIds drawPrism(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, float height) {
	float vertices[] = {
		// prism top
		p1.x, p1.y, p1.z,
		p2.x, p2.y, p2.z,
		p3.x, p3.y, p3.z,
		p4.x, p4.y, p4.z,

		// prism bottom
		p1.x, p1.y + height, p1.z,
		p2.x, p2.y + height, p2.z,
		p3.x, p3.y + height, p3.z,
		p4.x, p4.y + height, p4.z
	};

	int indices[] = { 
		0, 1, 2, 
		2, 3, 0, // top

		0, 4, 1, 
		1, 4, 5, // side

		5, 1, 2, 
		2, 5, 6, // side

		6, 2, 3, 
		3, 6, 7, // side

		7, 3, 0, 
		0, 7, 4, // side

		4, 5, 6, 
		6, 7, 4 // bottom
	};

	unsigned int vao, vbo, ebo;

	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));

	GLCall(glGenBuffers(1, &vbo));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

	GLCall(glGenBuffers(1, &ebo));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, NULL));
	GLCall(glEnableVertexAttribArray(0));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return { vao, 0, vbo, 0, ebo, 0, 0 };
}

extendedObjectIds drawDroplet(std::string img_path) {
	float vertices[] = {
		-0.25f, -0.50f, 0.0f, // positions 1
		0.0f, 0.0f, // texture coords 1

		0.25f, -0.50f, 0.0f, // positions 2
		1.0f, 0.0f, // texture coords 2

		0.25f, 0.50f, 0.0f, // positions 3
		1.0f, 1.0f, // texture coords 3

		-0.25f, 0.50f, 0.0f, // positions 4
		0.0f, 1.0f, // texture coords 4
	};

	unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };

	unsigned int VAO, VBO, EBO;

	// Gen Vertex Array
	GLCall(glGenVertexArrays(1, &VAO));
	glBindVertexArray(VAO);

	// Buffers in use
	GLCall(glGenBuffers(1, &VBO));
	GLCall(glGenBuffers(1, &EBO));

	// Vertex Data
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, NULL));
	GLCall(glEnableVertexAttribArray(0));

	// Element Buffer Data
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

	// Texture coord data
	GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float))));
	GLCall(glEnableVertexAttribArray(1));

	unsigned int texture1;
	GLCall(glGenTextures(1, &texture1));
	GLCall(glBindTexture(GL_TEXTURE_2D, texture1));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//std::cout << "IMAGE LOADING" << std::endl;
	stbi_set_flip_vertically_on_load(true);
	int width, height, nr_channels;
	unsigned char* img_data = stbi_load(img_path.c_str(), &width, &height, &nr_channels, 0);
	if (img_data) {
		std::printf("number of channels: %d\n", nr_channels);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	//std::cout << "FREEING IMAGE" << std::endl;
	stbi_image_free(img_data);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// allows for use of alpha channel / transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::cout << "leaving water droplet" << std::endl;
	return { VAO, 0, VBO, 0, EBO, 0, texture1, 0 };
}


intVector2 get_max_and_min(int* mat, unsigned int MAT_SIZE) {
	intVector2 minmax = { INT_MAX, INT_MIN };

	for (unsigned int i = 0; i < MAT_SIZE; i++) {
		int cur = mat[i];
		if (cur < minmax.x) minmax.x = cur;
		if (cur > minmax.y) minmax.y = cur;
	}

	return minmax;
}

float normalize_int(int val, int min, int max) {
	return 2 * (((float) val - min) / (max - min)) - 1;
}

/* 
* Return a matrix of extendedObjectIds 
*/
struct extendedObjectIds *drawMatrixPrisms(int* mat, unsigned int MAT_SIZE) {
	struct extendedObjectIds *plane_list = (struct extendedObjectIds *) malloc(sizeof(struct extendedObjectIds) * MAT_SIZE);
	assert(plane_list != NULL);

	struct intVector2 minmax = get_max_and_min(mat, MAT_SIZE);

	unsigned int index = 0;
	while (index < MAT_SIZE && index + 1 < MAT_SIZE) {
		float normed_l = normalize_int(mat[index], minmax.x, minmax.y);
		float normed_r = normalize_int(mat[index + 1], minmax.x, minmax.y);

		struct extendedObjectIds temp = drawPrism(
			glm::vec3(-1.0f, normed_l, 1.0f),
			glm::vec3(-1.0f, normed_l, -1.0f),
			glm::vec3(1.0f, normed_r, -1.0f),
			glm::vec3(1.0f, normed_r, 1.0f),
			1.0f
		);

		memcpy(&plane_list[index], &temp, sizeof(extendedObjectIds));
		index++;
	}

	return plane_list;
}

