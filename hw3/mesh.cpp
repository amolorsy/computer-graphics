#include "mesh.h"

Mesh::Mesh() {
}

Mesh::~Mesh() {
}

void Mesh::addVertex(glm::vec3 vertex) {
  mVertices.push_back(vertex);
}

void Mesh::addFace(Face face) {
  mFaces.push_back(face);
}

std::vector<glm::vec3> Mesh::getVertices() {
  return mVertices;
}

std::vector<Face> Mesh::getFaces() {
  return mFaces;
}
