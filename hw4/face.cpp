#include "face.h"

Face::Face() {
}

Face::Face(std::vector<int> vertexIndices, std::vector<int> normalIndices) {
  mVertexIndices = vertexIndices;
  mNormalIndices = normalIndices;
}

Face::~Face() {
}

void Face::setMaterialIndex(int materialIndex) {
  mMaterialIndex = materialIndex;
}

int Face::getMaterialIndex() {
  return mMaterialIndex;
}

void Face::setVertexIndices(std::vector<int> vertexIndices) {
  mVertexIndices = vertexIndices;
}

void Face::setNormalIndices(std::vector<int> normalIndices) {
  mNormalIndices = normalIndices;
}

std::vector<int> Face::getVertexIndices() {
  return mVertexIndices;
}

std::vector<int> Face::getNormalIndices() {
  return mNormalIndices;
}
