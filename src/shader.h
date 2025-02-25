#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <stdio.h>
#include <stdlib.h>

#include "logger.h"

static inline char* readShader(const char* path)
{
    FILE* file = fopen(path, "r");
    if (!file) {
        LOG_ERROR("Failed to open  shader file: %s\n", path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(size + 1);
    if (!buffer) {
        LOG_ERROR("Failed to allocate memory for shader: %s\n", path);
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, size, file);
    buffer[size] = '\0';

    fclose(file);
    return buffer;
}

static inline void printShaderCompileLog(GLuint shader)
{
    GLint shaderType = 0;
    GLint compiled = 0;
    GLint logLen = -1;

    glGetShaderiv(shader, GL_SHADER_TYPE, &shaderType);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);

    const char* typeStr = (shaderType == GL_VERTEX_SHADER) ? "VERTEX" :
        (shaderType == GL_FRAGMENT_SHADER) ? "FRAGMENT" :
        (shaderType == GL_GEOMETRY_SHADER) ? "GEOMETRY" : "UNKNOWN";

    if(compiled == GL_FALSE)
    {
        if(logLen < 1)
        {
            LOG_ERROR("%s::SHADER There were errors but there were no logs\n", shaderType);
            return;
        }

        char* log = malloc(logLen);
        if(log)
        {
            GLsizei len;
            glGetShaderInfoLog(shader, logLen, &len, log);
            if (len != logLen -1)
            {
                LOG_ERROR("WTF!?");
            }
            LOG_ERROR("%s::SHADER ERROR\n%s\n", typeStr, log);
            free(log);
        }
        else
        {
            LOG_ERROR("%s::SHADER ERROR Failed to allocate memory for logging error\n", typeStr);
        }
        return;
    }

    LOG_INFO("%s::SHADER compiled successfully!\n", typeStr);
}

static inline void printProgramLog(GLuint program)
{
    GLint attachedShaders;
    GLint linked;
    GLint logLen = -1;

    glGetProgramiv(program, GL_ATTACHED_SHADERS, &attachedShaders);
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);

    LOG_INFO("%d shaders attached to program", attachedShaders);

    if (linked == GL_FALSE)
    {
        if (logLen < 1)
        {
            LOG_ERROR("There were errors in the program but no error logs\n");
            return;
        }
        char* log = (char*)malloc(logLen);
        if(log)
        {
            GLsizei len;
            glGetProgramInfoLog(program, logLen, &len, log);
            LOG_ERROR("LINK::PROGRAM error %s", log);
            free(log);
        }
        else
        {
            LOG_ERROR("Could not allocate memory for logging in program\n");
            return;
        }
    }

    LOG_INFO("Linking programs successful\n");
}

static inline GLuint compileAndLinkShader(const char* vs, const char* fs)
{
    const GLchar* vsSrc[] = {readShader(vs)};
    LOG_DEBUG("%s\n", vsSrc[0]);
    if (!vsSrc[0])
    {
        LOG_ERROR("Failed to read Vertex shader at %s\n", vs);
    }
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, vsSrc, NULL);
    glCompileShader(vertexShader);
    printShaderCompileLog(vertexShader);

    const GLchar* fsSrc[] = {readShader(fs)};
    LOG_DEBUG("%s\n", fsSrc[0]);
    if (!fsSrc[0])
    {
        LOG_ERROR("Failed to read Fragment shader at %s\n", fs);
    }
    GLuint fragmentShader =  glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, fsSrc, NULL);
    glCompileShader(fragmentShader);
    printShaderCompileLog(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    printProgramLog(shaderProgram);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram; 
}

#endif
