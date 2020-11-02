#include "meshup/geom/TriangleMesh.h"

namespace meshup::geom {

void TriangleMesh::addFace(const Vertex& v1, const Vertex& v2, const Vertex& v3) {
   vertices.push_back(v1);
   vertices.push_back(v2);
   vertices.push_back(v3);
}
size_t TriangleMesh::getNrOfVertices() const {
   return vertices.size();
}

size_t TriangleMesh::getDataSize() const{
   return vertices.size() * sizeof(Vertex);
}

const Vertex* TriangleMesh::getData() const {
   return &vertices[0];
}

}// namespace meshup::geom