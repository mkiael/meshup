#include "meshup/ogl/Camera.h"

namespace meshup::ogl {

namespace {

constexpr glm::vec3 V_UP(0.f, 1.f, 0.f);
constexpr glm::quat Q_DIR(0.f, 0.f, 0.f, 1.f);

}// namespace

Camera::Camera() : target(0.f), rot(), distance(0.f) {
   setRotation(0.f, 0.f);
}

void Camera::setTarget(float x, float y, float z) {
   target = glm::vec3(x, y, z);
}
void Camera::setDistance(float dist) {
   distance = dist;
}

void Camera::setRotation(float x, float y) {
   glm::quat qx(glm::cos(x / 2.f), glm::sin(x / 2.f), 0.f, 0.f);
   glm::quat qy(glm::cos(y / 2.f), 0.f, glm::sin(y / 2.f), 0.f);
   rot = qy * qx;
}

glm::mat4 Camera::getViewMatrix() const {
   return glm::lookAt(rotate() * distance, target, V_UP);
}

glm::vec3 Camera::rotate() const {
   glm::quat qq = rot * Q_DIR * glm::inverse(rot);
   return glm::vec3(qq.x, qq.y, qq.z);
}

}// namespace meshup::ogl