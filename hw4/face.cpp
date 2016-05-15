#include "face.h"

Face::Face(std::vector<int> vertexIndices, std::vector<int> normalIndices) {
  mVertexIndices = vertexIndices;
  mNormalIndices = normalIndices;
}

Face::~Face() {
}

std::vector<int> Face::getVertexIndices() {
  return mVertexIndices;
}

std::vector<int> Face::getNormalIndices() {
  return mNormalIndices;
}
