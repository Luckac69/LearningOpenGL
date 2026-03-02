cmake_minimum_required(VERSION 3.20)
project(MyOpenGLProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

add_executable(myapp src/main.cpp)

target_link_libraries(myapp
    PRIVATE
    OpenGL::GL
    glfw
)
