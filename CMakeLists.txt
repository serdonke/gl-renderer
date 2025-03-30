cmake_minimum_required(VERSION 3.10)
project(learnopengl C)

set(CMAKE_C_STANDARD 11)
set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/external)

# Disable unnecessary GLFW features
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Disable documentation generation")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Disable example programs")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Disable tests")
set(GLFW_INSTALL OFF CACHE BOOL "Disable installation")
add_subdirectory(${EXTERNAL_DIR}/glfw-3.4)

add_library(glad STATIC ${EXTERNAL_DIR}/glad/src/glad.c)
target_include_directories(glad PUBLIC ${EXTERNAL_DIR}/glad/include)

option(CGLM_SHARED "Shared build" OFF)
option(CGLM_STATIC "Static build" ON)
option(CGLM_USE_C99 "" OFF) # C11 
option(CGLM_USE_TEST "Enable Tests" OFF) # for make check - make test
add_subdirectory(external/cglm/ EXCLUDE_FROM_ALL)
# Global compiler flags
add_library(compile_flags INTERFACE)
target_compile_options(compile_flags INTERFACE -Wall -Wextra -Wpedantic)

# Find all .c files in src/
file(GLOB EXE_SOURCES src/*.c)

# Create an executable for each .c file
foreach(SOURCE_FILE ${EXE_SOURCES})
    get_filename_component(EXE_NAME ${SOURCE_FILE} NAME_WE)  # Get file name without extension
    add_executable(${EXE_NAME} ${SOURCE_FILE} src/logger.h src/shader.h src/utils.h)
    target_link_libraries(${EXE_NAME} PRIVATE glfw glad cglm compile_flags)
    target_include_directories(${EXE_NAME} PRIVATE ${EXTERNAL_DIR}/stb)
    add_dependencies(${EXE_NAME} copy_shaders copy_textures)  # <- Added dependency
endforeach()

# Copy shaders to build directory (for CLion)
file(GLOB_RECURSE SHADER_FILES ${CMAKE_SOURCE_DIR}/src/shaders/*)
add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/shaders_dummy
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/shaders
        ${CMAKE_BINARY_DIR}/shaders
        DEPENDS ${SHADER_FILES}
)
add_custom_target(copy_shaders ALL DEPENDS ${CMAKE_BINARY_DIR}/shaders_dummy)

# Copy textures to build directory
file(GLOB_RECURSE TEXTURE_FILES ${CMAKE_SOURCE_DIR}/src/textures/*)
add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/textures_dummy
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/textures
        ${CMAKE_BINARY_DIR}/textures
        DEPENDS ${TEXTURE_FILES}
)
add_custom_target(copy_textures ALL DEPENDS ${CMAKE_BINARY_DIR}/textures_dummy)
