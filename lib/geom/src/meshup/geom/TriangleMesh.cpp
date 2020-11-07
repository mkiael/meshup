#include "meshup/geom/TriangleMesh.h"

#include "glm/geometric.hpp"

namespace meshup::geom {

namespace {

glm::vec3 calculateNormal(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c) {
   glm::vec3 normal = glm::cross(b - a, c - a);
   return glm::normalize(normal);
}

}// namespace

TriangleMesh::VertexRef TriangleMesh::addVertex(float x, float y, float z) {
   vertices.push_back({glm::vec3(x, y, z), glm::vec3(0.f)});
   vertexFaceMap.push_back(std::vector<FaceRef>());
   return vertexRefCounter++;
}

TriangleMesh::FaceRef TriangleMesh::addFace(TriangleMesh::VertexRef v1, TriangleMesh::VertexRef v2, TriangleMesh::VertexRef v3) {
   faces.push_back({{v1, v2, v3}, calculateNormal(vertices[v1].position, vertices[v2].position, vertices[v3].position)});

   vertexIndices.push_back(v1);
   vertexIndices.push_back(v2);
   vertexIndices.push_back(v3);

   vertexFaceMap[v1].push_back(faceRefCounter);
   vertexFaceMap[v2].push_back(faceRefCounter);
   vertexFaceMap[v3].push_back(faceRefCounter);

   return faceRefCounter++;
}

void TriangleMesh::calculateNormals() {
   for (auto vertRef : vertexIndices) {
      glm::vec3 vertexNormal(0.f);
      const auto& faceMap = vertexFaceMap[vertRef];
      for (auto faceRef : faceMap) {
         vertexNormal += faces[faceRef].normal;
      }
      vertices[vertRef].normal = glm::normalize(vertexNormal);
   }
}

TriangleMesh::Vertex& TriangleMesh::getVertex(TriangleMesh::VertexRef ref) {
   return vertices[ref];
}

const TriangleMesh::Vertex& TriangleMesh::getVertex(TriangleMesh::VertexRef ref) const {
   return vertices[ref];
}

size_t TriangleMesh::getNrOfVertexIndices() const {
   return vertexIndices.size();
}

size_t TriangleMesh::getVertexIndexDataSize() const {
   return vertexIndices.size() * sizeof(VertexRef);
}

const TriangleMesh::VertexRef* TriangleMesh::getVertexIndexData() const {
   return vertexIndices.data();
}

size_t TriangleMesh::getNrOfVertices() const {
   return vertices.size();
}

size_t TriangleMesh::getVertexDataSize() const {
   return vertices.size() * sizeof(Vertex);
}

const TriangleMesh::Vertex* TriangleMesh::getVertexData() const {
   return &vertices[0];
}

TriangleMesh::Face& TriangleMesh::getFace(FaceRef ref) {
   return faces[ref];
}

const TriangleMesh::Face& TriangleMesh::getFace(FaceRef ref) const {
   return faces[ref];
}

}// namespace meshup::geom