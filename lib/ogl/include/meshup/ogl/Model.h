#pragma once

#include "meshup/geom/TriangleMesh.h"

namespace meshup::ogl {

class Model {
public:
   Model();
   void render();

private:
   geom::TriangleMesh mesh;
   unsigned int vao;
   unsigned int vbo;
   unsigned int ibo;
};

}// namespace meshup::ogl