#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "ErrorManager.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cout << "Error!" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    // DRAWING A SQUARE
    float positions[] = {
        100.0f, 100.0f,  0.0f, 0.0f, // bottom left of square - 0
        200.0f, 100.0f,  1.0f, 0.0f, // bottom right - 1
        200.0f, 200.0f,  1.0f, 1.0f, // top right - 2
        100.0f, 200.0f, 0.0f,  1.0f  // top left - 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };


    glEnable(GL_BLEND);
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.push<float>(2);
    layout.push<float>(2);
    va.addBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    // generate orthogonal matrix for projection
    //                          X DOMAIN      Y DOMAIN      Z DOMAIN
    // CONVERTS OUR POSITION COORDINATES TO FIT WITHIN THIS DOMAIN
    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(200, 200, 0));

    // matrix multiplication goes from right to left, so we multiply MVP in reverse order
    glm::mat4 mvp = proj * view * model;

    Shader shader("res/shaders/Basic.shader");

    shader.Bind();
    shader.setUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
    shader.setUniformMat4f("u_ModelViewProjection", mvp); // sending our projection to our shader

    Texture texture("res/textures/Data_Heart.png");
    texture.Bind();
    shader.setUniform1i("u_Texture", 0);

    va.UnBind();
    shader.UnBind();
    vb.UnBind();
    ib.UnBind();

    Renderer renderer;

    float r = 0.0f;
    float increment = 0.05f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.Clear();
        shader.Bind();
        shader.setUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

        va.Bind();
        ib.Bind();

        renderer.Draw(va, ib, shader);

        if (r > 1.0f) {
            increment = -0.05f;
        } else if (r < 0.0f) {
            increment = 0.05f;
        }

        r += increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}