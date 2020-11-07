#include "meshup/loader/ObjLoader.h"

#include "catch2/catch.hpp"

#include <sstream>

using namespace meshup::geom;
using namespace meshup::loader;

namespace {

void checkVertex(const TriangleMesh& mesh, unsigned int index, float x, float y, float z) {
   const TriangleMesh::Vertex& v = mesh.getVertex(index);
   std::stringstream ss;
   ss << "Vertex index " << index;
   SECTION(ss.str()) {
      REQUIRE(v.position.x == x);
      REQUIRE(v.position.y == y);
      REQUIRE(v.position.z == z);
   }
}

void checkFace(const TriangleMesh& mesh, unsigned int index, unsigned int a, unsigned int b, unsigned int c) {
   const TriangleMesh::Face& f = mesh.getFace(index);
   std::stringstream ss;
   ss << "Face index " << index;
   SECTION(ss.str()) {
      REQUIRE(f.vertices[0] == a);
      REQUIRE(f.vertices[1] == b);
      REQUIRE(f.vertices[2] == c);
   }
}

}// namespace

TEST_CASE("SquareWithNormals") {
   TriangleMesh mesh = readObj("square_with_normals.obj");

   REQUIRE(mesh.getNrOfVertices() == 4U);

   checkVertex(mesh, 0, -1.f, 1.f, 0.f);
   checkVertex(mesh, 1, -1.f, -1.f, 0.f);
   checkVertex(mesh, 2, 1.f, 1.f, 0.f);
   checkVertex(mesh, 3, 1.f, -1.f, 0.f);

   checkFace(mesh, 0, 0, 1, 2);
   checkFace(mesh, 1, 2, 1, 3);
}