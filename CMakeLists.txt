cmake_minimum_required(VERSION 3.10)
project(3dRenderer VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(3dRenderer
    src/main.cpp
    src/glad.c

)

target_include_directories(3dRenderer PRIVATE dependencies)

target_link_libraries(3dRenderer glfw OpenGL::GL)
