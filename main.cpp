#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

const char *vertexShaderSource = R"(
  // Specifed the GLSL verstion
  #version 330 core 
  // Define input varabile for vertex postion
  layout (location = 0) in vec3 aPos; 
  void main(){
    // set the outpostion to the vertex
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); 
  }
)";

const char *fragmentShaderSource = R"(
  #version 330 core
  //Define out varable for frament color
  out vec4 FragColor;
  void main(){
    //sets the output color of the frament
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); 
  }

)";

std::vector<float> objectsVertices = {
    // start of the bottom of the cup
    // 0.0f,  -0.5f, 0.0f, // center
    // 0.3f,  -0.5f, 0.0f, // right
    // -0.3f, -0.5f, 0.0f, // left

    // start of top of the cup
    //  0.0f, 5.0f, 0.0f, // center
    //  0.4f, 0.0f, 0.0f, // right
    // -0.4f, 0.0f, 0.0f // left
    // Front cover
    -0.5f, 0.5f, 0.0f,  // top-left
    0.5f, 0.5f, 0.0f,   // top-right
    -0.5f, -0.5f, 0.0f, // bottom-left
    0.5f, 0.5f, 0.0f,   // top-right
    -0.5f, -0.5f, 0.0f, // bottom-left
    0.5f, -0.5f, 0.0f,  // bottom-right

    // Back cover
    -0.5f, 0.5f, -0.1f,  // top-left
    0.5f, 0.5f, -0.1f,   // top-right
    -0.5f, -0.5f, -0.1f, // bottom-left
    0.5f, 0.5f, -0.1f,   // top-right
    -0.5f, -0.5f, -0.1f, // bottom-left
    0.5f, -0.5f, -0.1f,  // bottom-right

    // Spine
    0.0f, 0.5f, 0.0f,  // top
    0.0f, -0.5f, 0.0f, // bottom
    0.0f, 0.5f, -0.1f, // top
    0.0f, -0.5f, 0.0f, // bottom
    0.0f, 0.5f, -0.1f, // top
    0.0f, -0.5f, -0.1f // bottom
};

// Funcktion toe chedcdk and pring gl errors
void checkGLError(const char *file, int line) {
  GLenum errorCode;
  while ((errorCode = glGetError()) != GL_NO_ERROR) {
    std::cerr << "GL error:" << errorCode << "at" << file << ":" << std::endl;
  }
}
// macro so i dont have put the same arguments everytime
#define glCheckError() checkGLError(__FILE__, __LINE__ - 1);

int main() {
  // Initialize GLFW
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    return -1;
  }

  // Create a windowed mode window and its OpenGL context
  GLFWwindow *window =
      glfwCreateWindow(800, 600, "OpenGL Window", nullptr, nullptr);
  if (!window) {
    std::cerr << "Failed to create GLFW window\n";
    glfwTerminate();
    return -1;
  }

  // Make the window's context current
  glfwMakeContextCurrent(window);

  // check to see if glew can init
  if (glewInit() != GLEW_OK) {
    std::cerr << "Faild to init GLEW\n";
    glfwTerminate();
    return -1;
  }

  // set up Vertex Array Object
  // set up Vertex Buffer Object
  unsigned int VAO, VBO;

  glGenVertexArrays(1, &VAO);
  glCheckError();
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, objectsVertices.size() * sizeof(float),
               objectsVertices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // unpind VAO VBO
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // shader compile
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);

  // shaderprogram  attach
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  //  shader link
  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);

  // TODO: vertex arry and buffer intalization

  // modle matrices for each object

  glm::mat4 modelBook = glm::mat4(1.0f);
  glm::mat4 modelPen = glm::mat4(1.0f);
  glm::mat4 modelGlasses = glm::mat4(1.0f);
  glm::mat4 modelTeacup = glm::mat4(1.0f);

  // TODO:: Apply Transformations
  // translation rotation scale

  // Loop until the user closes the window
  while (!glfwWindowShouldClose(window)) {
    // Render here

    glClear(GL_COLOR_BUFFER_BIT); // clearn color buffer

    glUseProgram(shaderProgram); // sets the shader program

    // TODO: set the model matrix uniform for each object
    unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelBook));

    // Bind VAO for the book
    glBindVertexArray(VAO);

    // draw the book object
    glDrawArrays(GL_TRIANGLES, 0, objectsVertices.size() / 3);

    glBindVertexArray(0);

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
  }

  // Terminate GLFW
  glfwTerminate();
  return 0;
}
