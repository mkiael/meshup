#pragma once

#include "meshup/geom/TriangleMesh.h"

#include <string>

namespace meshup::loader {

geom::TriangleMesh readObj(const std::string& fileName);

}// namespace meshup::loader