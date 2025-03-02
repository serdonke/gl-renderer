#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>

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

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "trongle-boi", NULL, NULL);

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
    
    float triangle[] = {
        0.0f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f,
       -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f
    };

    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    
    GLuint trongleProgram = compileAndLinkShader("shaders/triangle.vs", "shaders/triangle.fs");

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(trongleProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_LOOP, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
