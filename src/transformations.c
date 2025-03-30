#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <cglm/cglm.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "logger.h"
#include "utils.h"
#include "shader.h"

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 640

int main(void)
{
    glfwSetErrorCallback(logGLFWerror);

    GLFWwindow *window;

    if(!glfwInit())
    {
        LOG_ERROR("GLFW failed to initialize");
        return 1;
    }

    LOG_INFO("GLFW: %s", glfwGetVersionString());
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "trans-boi", NULL, NULL);

    if (window == NULL)
    {
        LOG_ERROR("Failed to initialize a GLFW window");
        glfwTerminate();
        return 2;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG_ERROR("Failed to initialize GLAD");
        return 3;
    }

    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
    LOG_INFO("Frame buffer width: %d", fbWidth);
    LOG_INFO("Frame buffer height: %d", fbHeight);
    glViewport(0, 0, fbWidth, fbHeight);

    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
