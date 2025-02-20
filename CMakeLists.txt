cmake_minimum_required(VERSION 3.10)
project(learnopengl C)
find_package(glfw3 REQUIRED) #NOTE: might need to make this robust
add_executable(main src/main.c src/glad.c)
target_include_directories(main PRIVATE include)
target_link_libraries(main PRIVATE glfw)

