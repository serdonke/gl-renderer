#define GLFW_INCLUDE_NONE

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>

#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH  1280

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
    "}\0";

void framebufferResizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
