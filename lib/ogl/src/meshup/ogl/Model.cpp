#include "meshup/ogl/Model.h"

#include "glad/glad.h"

#include "meshup/geom/TriangleMesh.h"

namespace meshup::ogl {

Model::Model() {
   geom::TriangleMesh::VertexRef v0 = mesh.addVertex(.5f, -.5f, .5f);
   geom::TriangleMesh::VertexRef v1 = mesh.addVertex(.5f, -.5f, -.5f);
   geom::TriangleMesh::VertexRef v2 = mesh.addVertex(.5f, .5f, -.5f);
   geom::TriangleMesh::VertexRef v3 = mesh.addVertex(.5f, .5f, .5f);
   geom::TriangleMesh::VertexRef v4 = mesh.addVertex(-.5f, -.5f, .5f);
   geom::TriangleMesh::VertexRef v5 = mesh.addVertex(-.5f, -.5f, -.5f);
   geom::TriangleMesh::VertexRef v6 = mesh.addVertex(-.5f, .5f, -.5f);
   geom::TriangleMesh::VertexRef v7 = mesh.addVertex(-.5f, .5f, .5f);

   mesh.addFace(v4, v0, v3);
   mesh.addFace(v4, v3, v7);
   mesh.addFace(v0, v1, v2);
   mesh.addFace(v0, v2, v3);
   mesh.addFace(v1, v5, v6);
   mesh.addFace(v1, v6, v2);
   mesh.addFace(v5, v4, v7);
   mesh.addFace(v5, v7, v6);
   mesh.addFace(v7, v3, v2);
   mesh.addFace(v7, v2, v6);
   mesh.addFace(v0, v1, v5);
   mesh.addFace(v0, v5, v4);

   mesh.calculateNormals();

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