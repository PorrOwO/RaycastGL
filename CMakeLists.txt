cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(raycastGL VERSION 0.1.0 LANGUAGES CXX C) 

find_package(OpenGL REQUIRED)

add_library(glad STATIC lib/glad/glad.c)
target_include_directories(glad PUBLIC lib/glad/include)

add_executable(raycastGL src/main.cpp)
target_link_libraries(raycastGL PRIVATE glfw OpenGL::GL glad)
