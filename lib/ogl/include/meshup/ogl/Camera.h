#pragma once

#include "glm/mat4x4.hpp"
#include "glm/gtc/quaternion.hpp"

namespace meshup::ogl {

class Camera {
public:
   Camera();

   void setTarget(float x, float y, float z);

   void setDistance(float dist);

   void setRotation(float x, float y);

   glm::mat4 getViewMatrix() const;

private:
   glm::vec3 rotate() const;

   glm::vec3 target;
   glm::quat rot;
   float distance;
};

}// namespace meshup::ogl