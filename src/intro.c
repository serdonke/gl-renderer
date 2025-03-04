#define GLFW_INCLUDE_NONE

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <math.h>
#include "utils.h"

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH  800

#include "shader.h"

int main (void) {
    GLFWwindow* window; 

    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WINDOW_WIDTH, 
            WINDOW_HEIGHT, "YEEEHAW", NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr, "Failed to initialize a GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fprintf(stderr, "Failed to initialize GLAD");
        return -2;
    }

    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
    printf("%d %d\n", fbWidth, fbHeight);
    glViewport(0, 0, fbWidth, fbHeight);

    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);


    GLuint shaderProgram = compileAndLinkShader("shaders/vertex.vs", "shaders/fragment.fs");

    float triangle[] = {
        // positions         // colors
        -0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.0f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };

    GLuint VBO, VAO; //, EBO;
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
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    GLint offset = glGetUniformLocation(shaderProgram, "move");
    
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glUniform1f(offset, 0.5);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
