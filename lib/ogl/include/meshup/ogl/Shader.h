#pragma once

#include "glm/fwd.hpp"

namespace meshup::ogl {

class Shader {
public:
   Shader();

   bool isValid() const;

   void use();

   void setModel(const glm::mat4& m);
   void setView(const glm::mat4& m);
   void setProjection(const glm::mat4& m);

private:
   unsigned int shaderProgramId;
   int modelLocation;
   int viewLocation;
   int projectionLocation;
};

}// namespace meshup::ogl