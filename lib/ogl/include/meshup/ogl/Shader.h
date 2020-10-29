#pragma once

namespace meshup::ogl {

class Shader {
public:
   static Shader create();
   bool isValid() const;
   void use();

private:
   explicit Shader(unsigned int _shaderProgramId);
   unsigned int shaderProgramId;
};

}// namespace meshup::ogl