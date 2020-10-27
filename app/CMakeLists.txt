project(meshup-app)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME}
    OpenGL::OpenGL
    glfw
    glad
    imgui-glfw-lib)