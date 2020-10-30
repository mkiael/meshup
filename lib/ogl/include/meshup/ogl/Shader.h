#pragma once

namespace meshup::ogl {

class Shader {
public:
   Shader();
   bool isValid() const;
   void use();

private:
   unsigned int shaderProgramId;
};

}// namespace meshup::ogl