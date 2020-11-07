#include "meshup/ogl/Model.h"

#include "glad/glad.h"

#include "meshup/geom/TriangleMesh.h"

namespace meshup::ogl {

Model::Model(const geom::TriangleMesh& _mesh) : mesh(_mesh) {
   glGenVertexArrays(1, &vao);
   glGenBuffers(1, &vbo);
   glGenBuffers(1, &ibo);

   glBindVertexArray(vao);

   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glBufferData(GL_ARRAY_BUFFER, mesh.getVertexDataSize(), mesh.getVertexData(), GL_STATIC_DRAW);

   const size_t vertexSize = mesh.getVertexDataSize() / mesh.getNrOfVertices();
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*) 0);
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*) sizeof(glm::vec3));
   glEnableVertexAttribArray(1);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.getVertexIndexDataSize(), mesh.getVertexIndexData(), GL_STATIC_DRAW);

   glBindVertexArray(0);
}

void Model::render() {
   glBindVertexArray(vao);
   glDrawElements(GL_TRIANGLES, mesh.getNrOfVertexIndices(), GL_UNSIGNED_INT, nullptr);
}

}// namespace meshup::ogl