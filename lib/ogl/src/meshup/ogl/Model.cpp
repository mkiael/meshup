#include "meshup/ogl/Model.h"

#include "glad/glad.h"

namespace meshup::ogl {

Model::Model() {
   float vertices[] = {
           -0.5f, -0.5f, -0.5f,
           0.5f, -0.5f, -0.5f,
           0.5f, 0.5f, -0.5f,
           0.5f, 0.5f, -0.5f,
           -0.5f, 0.5f, -0.5f,
           -0.5f, -0.5f, -0.5f,

           -0.5f, -0.5f, 0.5f,
           0.5f, -0.5f, 0.5f,
           0.5f, 0.5f, 0.5f,
           0.5f, 0.5f, 0.5f,
           -0.5f, 0.5f, 0.5f,
           -0.5f, -0.5f, 0.5f,

           -0.5f, 0.5f, 0.5f,
           -0.5f, 0.5f, -0.5f,
           -0.5f, -0.5f, -0.5f,
           -0.5f, -0.5f, -0.5f,
           -0.5f, -0.5f, 0.5f,
           -0.5f, 0.5f, 0.5f,

           0.5f, 0.5f, 0.5f,
           0.5f, 0.5f, -0.5f,
           0.5f, -0.5f, -0.5f,
           0.5f, -0.5f, -0.5f,
           0.5f, -0.5f, 0.5f,
           0.5f, 0.5f, 0.5f,

           -0.5f, -0.5f, -0.5f,
           0.5f, -0.5f, -0.5f,
           0.5f, -0.5f, 0.5f,
           0.5f, -0.5f, 0.5f,
           -0.5f, -0.5f, 0.5f,
           -0.5f, -0.5f, -0.5f,

           -0.5f, 0.5f, -0.5f,
           0.5f, 0.5f, -0.5f,
           0.5f, 0.5f, 0.5f,
           0.5f, 0.5f, 0.5f,
           -0.5f, 0.5f, 0.5f,
           -0.5f, 0.5f, -0.5f};

   glGenVertexArrays(1, &vao);
   glGenBuffers(1, &vbo);

   glBindVertexArray(vao);

   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
   glEnableVertexAttribArray(0);

   glBindVertexArray(0);
}

void Model::render() {
   glBindVertexArray(vao);
   glDrawArrays(GL_TRIANGLES, 0, 36);
}

}// namespace meshup::ogl