#include "meshup/ogl/Camera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace meshup::ogl {

Camera::Camera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up) : viewMatrix(glm::lookAt(position, target, up)) {
}

const glm::mat4& Camera::getViewMatrix() const {
   return viewMatrix;
}

}// namespace meshup::ogl