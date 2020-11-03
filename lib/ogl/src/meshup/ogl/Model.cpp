#include "meshup/ogl/Model.h"

#include "glad/glad.h"

#include "meshup/geom/TriangleMesh.h"

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

   for (size_t i = 0; i < 108;) {
      geom::Vertex v1;
      v1.position[0] = vertices[i++];
      v1.position[1] = vertices[i++];
      v1.position[2] = vertices[i++];

      geom::Vertex v2;
      v2.position[0] = vertices[i++];
      v2.position[1] = vertices[i++];
      v2.position[2] = vertices[i++];

      geom::Vertex v3;
      v3.position[0] = vertices[i++];
      v3.position[1] = vertices[i++];
      v3.position[2] = vertices[i++];

      mesh.addFace(v1, v2, v3);
   }

   glGenVertexArrays(1, &vao);
   glGenBuffers(1, &vbo);

   glBindVertexArray(vao);

   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glBufferData(GL_ARRAY_BUFFER, mesh.getDataSize(), mesh.getData(), GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(geom::Vertex), (void*) 0);
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(geom::Vertex), (void*) sizeof(glm::vec3));
   glEnableVertexAttribArray(1);

   glBindVertexArray(0);
}

void Model::render() {
   glBindVertexArray(vao);
   glDrawArrays(GL_TRIANGLES, 0, mesh.getNrOfVertices());
}

}// namespace meshup::ogl