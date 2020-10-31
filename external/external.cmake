include(FetchContent)
set(FETCHCONENT_QUITE FALSE)

#
# OpenGL
#

find_package(OpenGL REQUIRED COMPONENTS OpenGL)

#
# GLAD
#

FetchContent_Declare(glad
   GIT_REPOSITORY https://github.com/Dav1dde/glad.git
   GIT_TAG a5ca31c88a4cc5847ea012629aff3690f261c7c4 # 0.1.34
)

set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile")
set(GLAD_API "gl=3.3" CACHE STRING "API type/version pairs, like \"gl=3.2,gles=\", no version means latest")
set(GLAD_GENERATOR "c" CACHE STRING "Language to generate the binding for")

FetchContent_MakeAvailable(glad)

#
# GLFW
#

FetchContent_Declare(glfw
   GIT_REPOSITORY https://github.com/glfw/glfw
   GIT_TAG 0a49ef0a00baa3ab520ddc452f0e3b1e099c5589 # 3.3.2
)

set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

FetchContent_MakeAvailable(glfw)

#
# GLM
#

FetchContent_Declare(glm
        GIT_REPOSITORY https://github.com/g-truc/glm
        GIT_TAG bf71a834948186f4097caa076cd2663c69a10e1e # 0.9.9.8
)

FetchContent_MakeAvailable(glm)

#
# IMGUI
#

FetchContent_Declare(imgui
   GIT_REPOSITORY https://github.com/ocornut/imgui.git
   GIT_TAG e5cb04b132cba94f902beb6186cb58b864777012 # v1.79
)

FetchContent_GetProperties(imgui)
if(NOT imgui_POPULATED)
   FetchContent_Populate(imgui)

  set(IMGUI_SOURCES
     "${imgui_SOURCE_DIR}/imgui.cpp"
     "${imgui_SOURCE_DIR}/imgui_draw.cpp"
     "${imgui_SOURCE_DIR}/imgui_widgets.cpp"
     "${imgui_SOURCE_DIR}/examples/imgui_impl_glfw.cpp"
     "${imgui_SOURCE_DIR}/examples/imgui_impl_opengl3.cpp")

  set(IMGUI_LIB_NAME "imgui-glfw-lib")

  add_library(${IMGUI_LIB_NAME} ${IMGUI_SOURCES})

  add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)

  target_include_directories(${IMGUI_LIB_NAME}
    PUBLIC
      ${imgui_SOURCE_DIR}
      ${imgui_SOURCE_DIR}/examples
  )

  target_link_libraries(${IMGUI_LIB_NAME} OpenGL::OpenGL glad glfw)
endif()

#
# SPDLOG
#

FetchContent_Declare(spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog
        GIT_TAG cbe9448650176797739dbab13961ef4c07f4290f # 1.8.1
)

FetchContent_MakeAvailable(spdlog)