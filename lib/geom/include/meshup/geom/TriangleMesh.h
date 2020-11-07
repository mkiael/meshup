#pragma once

#include "glm/vec3.hpp"

#include <vector>

namespace meshup::geom {

// Very naive implementation of a triangle mesh
class TriangleMesh {
public:
   using VertexRef = unsigned int;
   using FaceRef = unsigned int;

   struct Vertex {
      glm::vec3 position;
      glm::vec3 normal;
   };

   struct Face {
      VertexRef vertices[3];
      glm::vec3 normal;
   };

   VertexRef addVertex(float x, float y, float z);
   FaceRef addFace(VertexRef v1, VertexRef v2, VertexRef v3);
   void calculateNormals();

   Vertex& getVertex(VertexRef ref);
   const Vertex& getVertex(VertexRef ref) const;

   size_t getNrOfVertexIndices() const;
   size_t getVertexIndexDataSize() const;
   const VertexRef* getVertexIndexData() const;

   size_t getNrOfVertices() const;
   size_t getVertexDataSize() const;
   const Vertex* getVertexData() const;

   Face& getFace(FaceRef ref);
   const Face& getFace(FaceRef ref) const;

private:
   std::vector<VertexRef> vertexIndices;
   std::vector<Vertex> vertices;
   std::vector<Face> faces;
   std::vector<std::vector<FaceRef>> vertexFaceMap;
   VertexRef vertexRefCounter{0U};
   FaceRef faceRefCounter{0U};
};

}// namespace meshup::geom