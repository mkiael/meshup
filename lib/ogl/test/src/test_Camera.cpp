#include "meshup/ogl/Camera.h"

#include "catch2/catch.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"

using namespace meshup::ogl;

namespace {

bool isMatricesEqual(const glm::mat4& m1, const glm::mat4& m2) {
   for (size_t i = 0; i < 4; ++i) {
      for (size_t j = 0; j < 3; ++j) {
         if (std::fabs(m1[i][j] - m2[i][j]) > 0.001f) {
            return false;
         }
      }
   }
   return true;
}

}// namespace

TEST_CASE("Set distance") {
   Camera camera;
   camera.setDistance(5.f);

   glm::mat4 expectedViewMatrix = glm::lookAt(glm::vec3(0.f, 0.f, 5.f),
                                              glm::vec3(0.f, 0.f, 0.f),
                                              glm::vec3(0.f, 1.f, 0.f));

   REQUIRE(isMatricesEqual(expectedViewMatrix, camera.getViewMatrix()));
}

TEST_CASE("Set positive X axis rotation") {
   Camera camera;
   camera.setDistance(1.f);
   camera.setRotation(glm::radians(30.f), 0.f);

   glm::mat4 expectedViewMatrix = glm::lookAt(glm::vec3(0.f, -.5f, .866f),
                                              glm::vec3(0.f, 0.f, 0.f),
                                              glm::vec3(0.f, 1.f, 0.f));

   REQUIRE(isMatricesEqual(expectedViewMatrix, camera.getViewMatrix()));
}

TEST_CASE("Set negative X axis rotation") {
   Camera camera;
   camera.setDistance(1.f);
   camera.setRotation(glm::radians(-30.f), 0.f);

   glm::mat4 expectedViewMatrix = glm::lookAt(glm::vec3(0.f, .5f, .866f),
                                              glm::vec3(0.f, 0.f, 0.f),
                                              glm::vec3(0.f, 1.f, 0.f));

   REQUIRE(isMatricesEqual(expectedViewMatrix, camera.getViewMatrix()));
}

TEST_CASE("Set positive Y axis rotation") {
   Camera camera;
   camera.setDistance(1.f);
   camera.setRotation(0.f, glm::radians(45.f));

   glm::mat4 expectedViewMatrix = glm::lookAt(glm::vec3(.707f, 0.f, .707f),
                                              glm::vec3(0.f, 0.f, 0.f),
                                              glm::vec3(0.f, 1.f, 0.f));

   REQUIRE(isMatricesEqual(expectedViewMatrix, camera.getViewMatrix()));
}

TEST_CASE("Set negative Y axis rotation") {
   Camera camera;
   camera.setDistance(1.f);
   camera.setRotation(0.f, glm::radians(-60.f));

   glm::mat4 expectedViewMatrix = glm::lookAt(glm::vec3(-.866f, 0.f, .5f),
                                              glm::vec3(0.f, 0.f, 0.f),
                                              glm::vec3(0.f, 1.f, 0.f));

   REQUIRE(isMatricesEqual(expectedViewMatrix, camera.getViewMatrix()));
}

TEST_CASE("Set rotation on both X and Y axis") {
    const float radX = glm::radians(45.f);
    const float radY = glm::radians(-45.f);

   Camera camera;
   camera.setDistance(1.f);
   camera.setRotation(radX, radY);

   glm::vec3 v(0.f, 0.f, 1.f);
   v = glm::rotateX(v, radX);
   v = glm::rotateY(v, radY);

   glm::mat4 expectedViewMatrix = glm::lookAt(v,
                                              glm::vec3(0.f, 0.f, 0.f),
                                              glm::vec3(0.f, 1.f, 0.f));

   REQUIRE(isMatricesEqual(expectedViewMatrix, camera.getViewMatrix()));
}