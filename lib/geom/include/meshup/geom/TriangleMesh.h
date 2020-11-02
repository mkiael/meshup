#pragma once

#include "meshup/geom/Vertex.h"

#include <vector>

namespace meshup::geom {

// Very naive implementation of a triangle mesh
class TriangleMesh {
public:
   void addFace(const Vertex& v1, const Vertex& v2, const Vertex& v3);
   size_t getNrOfVertices() const;
   size_t getDataSize() const;
   const Vertex* getData() const;

private:
   std::vector<Vertex> vertices;
};

}// namespace meshup::geom