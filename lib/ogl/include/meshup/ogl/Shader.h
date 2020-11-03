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

   void setLightColor(const glm::vec3& color);
   void setObjectColor(const glm::vec3& color);
   void setLightPosition(const glm::vec3& position);

private:
   unsigned int shaderProgramId;
   int modelLocation;
   int viewLocation;
   int projectionLocation;
   int lightColorLocation;
   int objectColorLocation;
   int lightPositionLocation;
};

}// namespace meshup::ogl