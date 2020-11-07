include(Catch)

project(test-meshup-loader)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/test_ObjLoader.cpp
)

configure_file(test_utils/square_with_normals.obj square_with_normals.obj COPYONLY)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
            Catch2::Catch2
            meshup-loader
)

catch_discover_tests(${PROJECT_NAME})