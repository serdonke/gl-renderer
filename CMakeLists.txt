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

file(GLOB SHADERS "src/shaders/*")
add_custom_target(
    shaders_target ALL
    DEPENDS ${SHADERS}
)

add_executable(main src/main.c src/logger.h src/main.h src/shader.h)
target_link_libraries(main PRIVATE glfw glad)

add_dependencies(main shaders_target)

add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/src/shaders $<TARGET_FILE_DIR:main>/shaders
)

target_compile_options(main PRIVATE 
    -Wall
    -Wextra
    -Wpedantic
)
