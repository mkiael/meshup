#include "meshup/ogl/Model.h"
#include "meshup/ogl/Shader.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glad/glad.h"

#include "GLFW/glfw3.h"

#include <iostream>

static void glfw_error_callback(int error, const char* description) {
   std::cerr << "GLFW error [" << error << "]: " << description << "\n";
}

int main (int argc, char** argv) {
   glfwSetErrorCallback(glfw_error_callback);

   if (!glfwInit()) {
      std::exit(EXIT_FAILURE);
   }

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

   GLFWwindow* window = glfwCreateWindow(1280, 720, "Meshup", NULL, NULL);
   if (!window) {
      std::exit(EXIT_FAILURE);
   }

   glfwMakeContextCurrent(window);
   glfwSwapInterval(1);

   if (gladLoadGL() == 0) {
      std::cerr << "Failed to initialize OpenGL loader\n";
      std::exit(EXIT_FAILURE);
   }

   ImGui::CreateContext();
   ImGui::StyleColorsDark();
   ImGui_ImplGlfw_InitForOpenGL(window, true);
   ImGui_ImplOpenGL3_Init("#version 330" /* glsl version string*/);

   meshup::ogl::Shader shader;
   if (!shader.isValid()) {
      std::exit(EXIT_FAILURE);
   }

   meshup::ogl::Model model;

   ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

   while (!glfwWindowShouldClose(window)) {
      glfwPollEvents();

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      int display_w, display_h;
      glfwGetFramebufferSize(window, &display_w, &display_h);

      glViewport(0, 0, display_w, display_h);
      glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
      glClear(GL_COLOR_BUFFER_BIT);

      shader.use();
      model.render();

      ImGui::Begin("Hello");
      ImGui::Text("World!");
      ImGui::End();

      // Rendering
      ImGui::Render();

      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      glfwSwapBuffers(window);
   }

   ImGui_ImplOpenGL3_Shutdown();
   ImGui_ImplGlfw_Shutdown();
   ImGui::DestroyContext();

   glfwDestroyWindow(window);
   glfwTerminate();

   return 0;
}
