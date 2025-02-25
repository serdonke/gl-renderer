#define GLFW_INCLUDE_NONE

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <math.h>

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH  800

void framebufferResizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
