#include "meshup/ogl/Shader.h"

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
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
           "\n"
           "layout (location= 0) in vec3 inVertexPos;\n"
           "layout (location = 1) in vec3 inVertexNormal;\n"
           "\n"
           "out ShaderData {\n"
           "   vec3 fragmentPos;\n"
           "   vec3 vertexNormal;\n"
           "} o;\n"
           "\n"
           "uniform mat4 model;\n"
           "uniform mat4 view;\n"
           "uniform mat4 projection;\n"
           "\n"
           "void main() {\n"
           "   gl_Position = projection * view * model * vec4(inVertexPos.x, inVertexPos.y, inVertexPos.z, 1.0);\n"
           "   o.fragmentPos = vec3(model * vec4(inVertexPos, 1.0));\n"
           "   o.vertexNormal = inVertexNormal;\n"
           "}\0";

   const char* fragmentShaderSource =
           "#version 330 core\n"
           "\n"
           "in ShaderData {\n"
           "   vec3 fragmentPos;\n"
           "   vec3 vertexNormal;\n"
           "} i;\n"
           "\n"
           "out vec4 FragColor;\n"
           "\n"
           "uniform vec3 lightColor;\n"
           "uniform vec3 objectColor;\n"
           "uniform vec3 lightPosition;\n"
           "\n"
           "void main() {\n"
           "   float ambientFactor = 0.1;\n"
           "   vec3 ambient = ambientFactor * lightColor;\n"
           "   vec3 lightDirection = normalize(lightPosition - i.fragmentPos);\n"
           "   vec3 vertexNormal = normalize(i.vertexNormal);\n"
           "   vec3 diffuse = max(dot(vertexNormal, lightDirection), 0.0) * lightColor;\n"
           "   vec3 color = (ambient + diffuse) * objectColor;\n"
           "   FragColor = vec4(color, 1.0);\n"
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

Shader::Shader() : shaderProgramId(0), modelLocation(-1), viewLocation(-1), projectionLocation(-1), lightColorLocation(-1), objectColorLocation(-1), lightPositionLocation(-1) {
   shaderProgramId = createShader();
   modelLocation = glGetUniformLocation(shaderProgramId, "model");
   viewLocation = glGetUniformLocation(shaderProgramId, "view");
   projectionLocation = glGetUniformLocation(shaderProgramId, "projection");
   lightColorLocation = glGetUniformLocation(shaderProgramId, "lightColor");
   objectColorLocation = glGetUniformLocation(shaderProgramId, "objectColor");
   lightPositionLocation = glGetUniformLocation(shaderProgramId, "lightPosition");
}

bool Shader::isValid() const {
   return shaderProgramId != 0 && modelLocation != -1 && viewLocation != -1 && projectionLocation != -1 && lightColorLocation != -1 && objectColorLocation != -1 && lightPositionLocation != -1;
}

void Shader::use() {
   glUseProgram(shaderProgramId);
}

void Shader::setModel(const glm::mat4& m) {
   glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::setView(const glm::mat4& m) {
   glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::setProjection(const glm::mat4& m) {
   glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::setLightColor(const glm::vec3& color) {
   glUniform3fv(lightColorLocation, 1, &color[0]);
}

void Shader::setObjectColor(const glm::vec3& color) {
   glUniform3fv(objectColorLocation, 1, &color[0]);
}

void Shader::setLightPosition(const glm::vec3& position) {
   glUniform3fv(lightPositionLocation, 1, &position[0]);
}

}// namespace meshup::ogl