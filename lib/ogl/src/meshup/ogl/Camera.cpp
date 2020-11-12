#include "meshup/ogl/Camera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace meshup::ogl {

Camera::Camera(const glm::vec3& _target) : target(_target), direction(0.f, 0.f, 1.f), up(0.f, 1.f, 0.f), distance(0.f) {
}

void Camera::setDistance(float dist) {
   distance = dist;
}

glm::mat4 Camera::getViewMatrix() const {
   return glm::lookAt(direction * distance, target, up);
}

}// namespace meshup::ogl