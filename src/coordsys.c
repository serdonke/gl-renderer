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

float mixvalue = 0.5f;
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    if(yoffset < 0 && mixvalue > 0.0)
    {
        mixvalue -= 0.09f;
        return;
    } else if (yoffset > 0 && mixvalue < 1.0)
    {    
        mixvalue += 0.09f;
    }
    return;
}

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

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "coord-boi", NULL, NULL);

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

    GLuint trongleProgram = compileAndLinkShader("shaders/coordsys.vs", "shaders/coordsys.fs");

    // woops
 
    float quad[] = {
        // Front face
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,  // Top-left
        0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,  // Top-right
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,  // Bottom-right
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,  // Top-left
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,  // Bottom-right
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f,  // Bottom-left

        // Back face
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,

        // Left face
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,

        // Right face
        0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,

        // Top face
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,

        // Bottom face
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f
    };

    GLuint VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    stbi_set_flip_vertically_on_load(1);
    int width, height, nrChannels;
    unsigned char* image = stbi_load("textures/boi.jpg", &width, &height, &nrChannels, 0);
    if(!image)
    {
        LOG_ERROR("FAILED to load image");
        exit(69);
    }
    LOG_INFO("Loaded texture with %d x %d with %d channels", width, height, nrChannels);

    // Thanks for the fisting session opengl
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    GLuint gato;
    glGenTextures(1, &gato);
    glBindTexture(GL_TEXTURE_2D, gato);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(image);

    unsigned char* image2 = stbi_load("textures/gato.png", &width, &height, &nrChannels, 4);
    if(!image2)
    {
        LOG_ERROR("FAILED to load image");
        exit(69);
    }
    LOG_INFO("Loaded texture with %d x %d with %d channels", width, height, nrChannels);

    GLuint gato2;
    glGenTextures(1, &gato2);
    glBindTexture(GL_TEXTURE_2D, gato2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image2);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(image2);

    glBindVertexArray(0);

    glUseProgram(trongleProgram);
    glUniform1i(glGetUniformLocation(trongleProgram, "texture1"), 0);
    glUniform1i(glGetUniformLocation(trongleProgram, "texture2"), 1);
    glfwSetScrollCallback(window, scrollCallback);

    mat4 model = GLM_MAT4_IDENTITY_INIT;
    mat4 view = GLM_MAT4_IDENTITY_INIT;
    glm_translate(view, (vec3){0.0f, 0.0f, -3.0f});
    mat4 projection;
    glm_perspective(glm_rad(55.0f),(float)WINDOW_WIDTH/(float)WINDOW_HEIGHT,0.1f,100.0f,projection);

    GLint modelLoc = glGetUniformLocation(trongleProgram, "model");
    GLint viewLoc = glGetUniformLocation(trongleProgram, "view");
    GLint projLoc =  glGetUniformLocation(trongleProgram, "projection");
    
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model[0]);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view[0]);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, projection[0]);
    
    vec3 cubePositions[] = {
        { 0.0f,  0.0f,  0.0f}, 
        { 2.0f,  5.0f, -15.0f}, 
        {-1.5f, -2.2f, -2.5f},  
        {-3.8f, -2.0f, -12.3f},  
        { 2.4f, -0.4f, -3.5f},  
        {-1.7f,  3.0f, -7.5f},  
        { 1.3f, -2.0f, -2.5f},  
        { 1.5f,  2.0f, -2.5f}, 
        { 1.5f,  0.2f, -1.5f}, 
        {-1.3f,  1.0f, -1.5f} 
    }; 
     
    glEnable(GL_DEPTH_TEST);
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gato);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, gato2);

        glUniform1f(glGetUniformLocation(trongleProgram, "mixvalue"), mixvalue);
        glUseProgram(trongleProgram);
        glBindVertexArray(VAO);
        for(size_t i = 0;i<10;i++)
        {
            mat4 model = GLM_MAT4_IDENTITY_INIT;
            glm_translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            if (i % 3 == 0)
            {
                angle = glfwGetTime() * 25.0f;
            }

            glm_rotate(model, glm_rad(angle), (vec3){1.0f, 0.3f, 0.5f});
            
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model[0]);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &gato);
    glDeleteProgram(trongleProgram);

    glfwTerminate();
    return 0;
}

