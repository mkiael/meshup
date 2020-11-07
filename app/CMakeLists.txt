project(meshup-app C CXX)

add_executable(${PROJECT_NAME} src/main.cpp)

target_compile_features(${PROJECT_NAME}
        PRIVATE
            cxx_std_17
)

target_link_libraries(${PROJECT_NAME}
        OpenGL::GL
        glfw
        glad
        imgui-glfw-lib
        meshup-ogl
)