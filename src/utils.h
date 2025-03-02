#ifndef UTILS_H
#define UTILS_H

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stdbool.h>

#include "logger.h"

void framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void logGLFWerror(int code, const char* description)
{
    LOG_ERROR("GLFW error %d: %s", code, description);
}

#endif
