cmake_minimum_required(VERSION 3.20)
project(MyOpenGLProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

# Glad
add_library(glad src/glad.c)
target_include_directories(glad PUBLIC include)

# Executible
add_executable(myapp src/main.cpp src/Shader.cpp)

target_link_libraries(myapp PRIVATE glad OpenGL::GL glfw)
