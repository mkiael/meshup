#include "meshup/ogl/Shader.h"

#include "glad/glad.h"
#include "spdlog/spdlog.h"

namespace meshup::ogl {

namespace {

constexpr size_t INFO_LOG_SIZE = 512;

unsigned int compileShader(unsigned int shaderType, const std::string& shaderCode) {
   unsigned int shaderId = glCreateShader(shaderType);
   const char* src = shaderCode.c_str();
   glShaderSource(shaderId, 1, &src, nullptr);
   glCompileShader(shaderId);

   int result = 0;
   glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
   if (result) {
      return shaderId;
   } else {
      char log[INFO_LOG_SIZE];
      glGetShaderInfoLog(shaderId, INFO_LOG_SIZE, nullptr, log);
      spdlog::error("Failed to compile vertex shader: {}", log);
      return 0;
   }
}

unsigned int createShader() {
   const char* vertexShaderSource =
           "#version 330 core\n"
           "layout (location= 0) in vec3 aPos;\n"
           "void main() {\n"
           "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
           "}\0";

   const char* fragmentShaderSource =
           "#version 330 core\n"
           "out vec4 FragColor;\n"
           "void main() {\n"
           "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
           "}\0";

   unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
   if (!vertexShader) {
      return 0;
   }

   unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
   if (!fragmentShader) {
      return 0;
   }

   unsigned int shaderProgram = glCreateProgram();
   glAttachShader(shaderProgram, vertexShader);
   glAttachShader(shaderProgram, fragmentShader);
   glLinkProgram(shaderProgram);

   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);

   int result = 0;
   glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
   if (result) {
      return shaderProgram;
   } else {
      char log[INFO_LOG_SIZE];
      glGetProgramInfoLog(shaderProgram, INFO_LOG_SIZE, nullptr, log);
      spdlog::error("Failed to link shader program: {}", log);
      return 0;
   }
}

}// namespace

Shader Shader::create() {
   return Shader(createShader());
}

Shader::Shader(unsigned int _shaderProgramId) : shaderProgramId(_shaderProgramId) {
}

bool Shader::isValid() const {
   return shaderProgramId != 0;
}

void Shader::use() {
   glUseProgram(shaderProgramId);
}

}// namespace meshup::ogl