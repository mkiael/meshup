#pragma once

#include "glm/mat4x4.hpp"

namespace meshup::ogl {

class Camera {
public:
   Camera(const glm::vec3& position,
          const glm::vec3& target,
          const glm::vec3& up);

   const glm::mat4& getViewMatrix() const;

private:
   glm::mat4 viewMatrix;
};

}// namespace meshup::ogl