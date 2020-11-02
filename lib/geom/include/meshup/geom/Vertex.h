#pragma once

#include "glm/vec3.hpp"

namespace meshup::geom {

struct Vertex {
   glm::vec3 position;
   glm::vec3 normal;
};

}// namespace meshup::geom