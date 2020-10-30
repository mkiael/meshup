#pragma once

namespace meshup::ogl {

class Model {
public:
   Model();
   void render();

private:
   unsigned int vao;
   unsigned int vbo;
};

}// namespace meshup::ogl