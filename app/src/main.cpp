#include "meshup/loader/ObjLoader.h"
#include "meshup/ogl/Model.h"
#include "meshup/ogl/Shader.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glad/glad.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "GLFW/glfw3.h"

#include <iostream>

namespace {

constexpr int WIN_WIDTH = 1280;
constexpr int WIN_HEIGHT = 720;

}// namespace

static void glfw_error_callback(int error, const char* description) {
   std::cerr << "GLFW error [" << error << "]: " << description << "\n";
}

int main(int argc, char** argv) {
   glfwSetErrorCallback(glfw_error_callback);

   if (!glfwInit()) {
      std::exit(EXIT_FAILURE);
   }

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

   GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Meshup", NULL, NULL);
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

   glEnable(GL_DEPTH_TEST);

   meshup::ogl::Shader shader;
   if (!shader.isValid()) {
      std::exit(EXIT_FAILURE);
   }

   shader.use();

   auto projMat = glm::perspective(glm::radians(45.f), (float) WIN_WIDTH / (float) WIN_HEIGHT, 0.1f, 100.f);
   shader.setProjection(projMat);

   auto viewMat = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -5.f));
   shader.setView(viewMat);

   shader.setLightColor(glm::vec3(1.f, 1.f, 1.f));
   shader.setObjectColor(glm::vec3(.5f, .2f, .1f));

   auto mesh = meshup::loader::readObj("assets/utah_teapot.obj");
   mesh.calculateNormals();
   meshup::ogl::Model model(mesh);

   ImVec4 clear_color = ImVec4(.0f, .0f, .0f, 1.f);

   float pitchAngle = 0.f;
   float yawAngle = 0.f;

   float lightX = 10.f;
   float lightY = 10.f;
   float lightZ = -10.f;

   while (!glfwWindowShouldClose(window)) {
      glfwPollEvents();

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      int display_w, display_h;
      glfwGetFramebufferSize(window, &display_w, &display_h);

      glViewport(0, 0, display_w, display_h);
      glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      shader.use();

      shader.setLightPosition(glm::vec3(lightX, lightY, lightZ));

      auto modelMat = glm::mat4(1.f);
      modelMat = glm::rotate(modelMat, glm::radians(pitchAngle), glm::vec3(1.f, 0.f, 0.f));
      modelMat = glm::rotate(modelMat, glm::radians(yawAngle), glm::vec3(0.f, 1.f, 0.f));
      shader.setModel(modelMat);

      model.render();

      ImGui::Begin("Object");
      ImGui::SliderFloat("Pitch", &pitchAngle, 0.f, 360.f);
      ImGui::SliderFloat("Yaw", &yawAngle, 0.f, 360.f);
      ImGui::End();

      ImGui::Begin("Light");
      ImGui::SliderFloat("Light X", &lightX, -10.f, 10.f);
      ImGui::SliderFloat("Light Y", &lightY, -10.f, 10.f);
      ImGui::SliderFloat("Light Z", &lightZ, -10.f, 10.f);
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