#include "meshup/loader/ObjLoader.h"

#include <fstream>
#include <sstream>
#include <vector>

namespace meshup::loader {

struct ObjFace {
   std::vector<unsigned int> vi;
   std::vector<unsigned int> ti;
   std::vector<unsigned int> ni;
};

unsigned int castIndex(const std::string& str) {
   return std::stoi(str) - 1;
}

std::vector<float> parseVertices(std::istringstream& iss) {
   std::vector<float> v;
   for (std::string token; std::getline(iss, token, ' ');) {
      v.push_back(std::stof(token));
   }
   return v;
}

ObjFace parseFaceElements(std::istringstream& iss) {
   ObjFace f;
   size_t i = 0U;
   for (std::string token; std::getline(iss, token, ' '); ++i) {
      if (size_t pos = token.find("//"); pos != std::string::npos) {
         f.vi.push_back(castIndex(token.substr(0, pos)));
         f.ni.push_back(castIndex(token.substr(pos + 2, token.size())));
      } else if (size_t pos = token.find('/'); pos != std::string::npos) {
         f.vi.push_back(castIndex(token.substr(0, pos)));
         std::string nextToken = token.substr(pos + 1, token.size());
         if (size_t nextPos = nextToken.find('/'); nextPos != std::string::npos) {
            f.ti.push_back(castIndex(nextToken.substr(0, nextPos)));
            f.ni.push_back(castIndex(nextToken.substr(nextPos + 1, nextToken.size())));
         } else {
            f.ti.push_back(castIndex(nextToken.substr(0, token.size())));
         }
      } else {
         f.vi.push_back(castIndex(token));
      }
   }
   return f;
}

geom::TriangleMesh readObj(const std::string& fileName) {
   std::ifstream fs(fileName);
   if (fs.bad()) {
      return geom::TriangleMesh();
   }
   std::string line;
   geom::TriangleMesh mesh;
   for (std::string line; std::getline(fs, line);) {
      std::istringstream iss(line);
      for (std::string token; std::getline(iss, token, ' ');) {
         if (token == "#") {
            break;
         } else if (token == "v") {
            std::vector<float> v = parseVertices(iss);
            if (v.size() == 3U) {
               mesh.addVertex(v[0], v[1], v[2]);
            }
         } else if (token == "f") {
            ObjFace f = parseFaceElements(iss);
            if (f.vi.size() == 3U) {
               mesh.addFace(f.vi[0], f.vi[1], f.vi[2]);
            }
         }
      }
   }
   return mesh;
}

}// namespace meshup::loader