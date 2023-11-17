#include <cstddef>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char *vertexShaderSource;

const char *fragmentShaderSource;

std::vector<float> objectsVertices = {
    // start of the bottom of the cup
    0.0f, -0.5f, 0.0f,  // center
    0.3f, -0.5f, 0.0f,  // right
    -0.3f, -0.5f, 0.0f, // left

    // start of top of the cup
    0.0f, 5.0f, 0.0f, // center
    0.4f, 0.0f, 0.0f, // right
    -0.4f, 0.0f, 0.0f // left
};

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Window", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // TODO: shader compliation and linking

    // TODO: vertex arry and buffer intalization

    // modle matrices for each object

    glm::mat4 modelBook = glm::mat4(1.0f);
    glm::mat4 modelPen = glm::mat4(1.0f);
    glm::mat4 modelGlasses = glm::mat4(1.0f);
    glm::mat4 modelTeacup = glm::mat4(1.0f);

    //TODO:: Apply Transformations 
    //translation rotation scale

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Render here

        glClear(GL_COLOR_BUFFER_BIT); //clearn color buffer

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
    return 0;
}
