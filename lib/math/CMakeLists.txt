project(meshup-math CXX)

add_library(${PROJECT_NAME}
    include/meshup/math/vec3.h
    src/meshup/math/vec3.cpp
)

target_compile_features(${PROJECT_NAME}
    PRIVATE
        cxx_std_17
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        include
    PRIVATE
        src
)