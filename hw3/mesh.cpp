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

void Mesh::clearVertices() {
  mVertices.clear();
}

void Mesh::clearFaces() {
  mFaces.clear();
}

void Mesh::generateStlFile() {
  std::ofstream file;
  file.open("bulb.stl");
  
  file << "solid bulb" << std::endl;
  for (int i = 0; i < mFaces.size(); i++) {
    std::vector<int> indices = mFaces.at(i).getIndices();
    glm::vec3 v1 = mVertices.at(indices.at(0));
    glm::vec3 v2 = mVertices.at(indices.at(1));
    glm::vec3 v3 = mVertices.at(indices.at(2));
    glm::vec3 normal = glm::cross(v2 - v1, v3 - v1);
    
    if (!glm::length(normal) == 0.0f) {
      normal = glm::normalize(normal);

      file << "  facet normal " << normal.x << " " << normal.y << " " << normal.z << std::endl;
      file << "    outer loop" << std::endl;
      file << "      vertex " << v1.x << " " << v1.y << " " << v1.z << std::endl;
      file << "      vertex " << v2.x << " " << v2.y << " " << v2.z << std::endl;
      file << "      vertex " << v3.x << " " << v3.y << " " << v3.z << std::endl;
      file << "    endloop" << std::endl;
      file << "  endfacet" << std::endl;
    }
  }
  file << "endsolid" << std::endl;

  file.close();
}
