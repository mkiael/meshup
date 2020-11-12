#pragma once

#include "glm/mat4x4.hpp"

namespace meshup::ogl {

class Camera {
public:
   Camera(const glm::vec3& _target);

   void setDistance(float dist);

   glm::mat4 getViewMatrix() const;

private:
   glm::vec3 target;
   glm::vec3 direction;
   glm::vec3 up;
   float distance;
};

}// namespace meshup::ogl