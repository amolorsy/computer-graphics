#include "face.h"

Face::Face(std::vector<int> indices) {
  mIndices = indices;
}

Face::~Face() {
}

std::vector<int> Face::getIndices() {
  return mIndices;
}
