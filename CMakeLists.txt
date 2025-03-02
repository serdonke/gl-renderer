cmake_minimum_required(VERSION 3.10)
project(learnopengl C)

set(CMAKE_C_STANDARD 11)

set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/external)

# DearGLFW please stahp
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Disable documentation generation")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Disable example programs")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Disable tests")
set(GLFW_INSTALL OFF CACHE BOOL "Disable installation")
add_subdirectory(${EXTERNAL_DIR}/glfw-3.4)

add_library(glad STATIC ${EXTERNAL_DIR}/glad/src/glad.c)
target_include_directories(glad PUBLIC ${EXTERNAL_DIR}/glad/include)

# Yea I hate you too cmake
add_library(compile_flags INTERFACE)
target_compile_options(compile_flags INTERFACE -Wall -Wextra -Wpedantic)

add_executable(main src/main.c src/logger.h src/main.h src/shader.h)
target_link_libraries(main PRIVATE glfw glad compile_flags)

add_executable(triangle src/triangle.c src/logger.h src/shader.h)
target_link_libraries(triangle PRIVATE glfw glad compile_flags)

# Make sure shader is copied because clion is retarded
file(GLOB_RECURSE SHADER_FILES ${CMAKE_SOURCE_DIR}/src/shaders/*)
add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/shaders_dummy
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/shaders
        ${CMAKE_BINARY_DIR}/shaders
        DEPENDS ${SHADER_FILES}
)
add_custom_target(copy_shaders ALL DEPENDS ${CMAKE_BINARY_DIR}/shaders_dummy)

add_dependencies(main copy_shaders)
add_dependencies(triangle copy_shaders)