include(Catch)

project(test-meshup-ogl)

add_executable(${PROJECT_NAME}
        src/main.cpp
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
            Catch2::Catch2
            meshup-ogl
)

catch_discover_tests(${PROJECT_NAME})