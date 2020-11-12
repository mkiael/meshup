#include "meshup/ogl/Camera.h"

#include "catch2/catch.hpp"

#include "glm/gtc/matrix_transform.hpp"

using namespace meshup::ogl;

TEST_CASE("SetDistance") {
   glm::vec3 position(0.f, 0.f, 5.f);
   glm::vec3 target(0.f, 0.f, 0.f);
   glm::vec3 up(0.f, 1.f, 0.f);

   glm::mat4 expectedViewMatrix = glm::lookAt(position, target, up);

   Camera camera(target);
   camera.setDistance(5.f);

   REQUIRE(expectedViewMatrix == camera.getViewMatrix());
}