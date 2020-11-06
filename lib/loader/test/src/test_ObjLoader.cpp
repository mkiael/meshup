#include "meshup/loader/ObjLoader.h"

#include "catch2/catch.hpp"

using namespace meshup::geom;
using namespace meshup::loader;

TEST_CASE("MeshHasZeroVertices") {
   TriangleMesh mesh = readObj("test.obj");
   REQUIRE(mesh.getNrOfVertices() == 0U);
   REQUIRE(mesh.getNrOfVertexIndices() == 0U);
}