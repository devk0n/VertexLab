cmake_minimum_required(VERSION 3.10)
project(VertexLab)

set(CMAKE_CXX_STANDARD 17)

# Source Files
add_executable(VertexLab
        main.cpp
        camera.cpp
        callbacks.cpp
        backends/imgui_impl_glfw.cpp
        backends/imgui_impl_opengl3.cpp
        imgui_manager.cpp
        imgui_manager.h
        imgui_widgets.cpp
        imgui_widgets.h
        drawing_utils.cpp
        drawing_utils.h
        utils.cpp
        utils.h
        shader.cpp
        shader.h
)

# Libraries
find_package(glfw3 REQUIRED)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Include Directories
target_include_directories(VertexLab PRIVATE backends)

# Link Libraries
target_link_libraries(VertexLab PRIVATE GLEW::GLEW imgui glfw OpenGL::GL)
