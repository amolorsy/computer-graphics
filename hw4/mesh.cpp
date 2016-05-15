#include "mesh.h"

Mesh::Mesh() {
}

Mesh::~Mesh() {
}

void Mesh::addVertex(glm::vec3 vertex) {
  mVertices.push_back(vertex);
}

void Mesh::addNormal(glm::vec3 normal) {
  mNormals.push_back(normal);
}

void Mesh::addFace(Face face) {
  mFaces.push_back(face);
}

std::vector<glm::vec3> Mesh::getVertices() {
  return mVertices;
}

std::vector<glm::vec3> Mesh::getNormals() {
  return mNormals; 
}

std::vector<Face> Mesh::getFaces() {
  return mFaces;
}

void Mesh::clearVertices() {
  mVertices.clear();
}

void Mesh::clearNormals() {
  
}

void Mesh::clearFaces() {
  mFaces.clear();
}

Mesh Mesh::fromObjFile(std::string filePath) {
  Mesh mesh;
  std::ifstream fin(filePath.c_str());
  std::string line;

  while (!fin.eof()) {
    std::getline(fin, line);
    removeComment(line);
    trim(line);

    std::stringstream stream(line);
    std::vector<std::string> tokens;
    std::string token;
    while (stream >> token) tokens.push_back(token);

    if (tokens.size() == 0) continue;
    else if (tokens.at(0).compare("v") == 0) {
      mesh.addVertex(glm::vec3(
            atof(tokens.at(1).c_str()),
            atof(tokens.at(2).c_str()),
            atof(tokens.at(3).c_str())));
    }
    else if (tokens.at(0).compare("vn") == 0) {
      mesh.addNormal(glm::vec3(
            atof(tokens.at(1).c_str()),
            atof(tokens.at(2).c_str()),
            atof(tokens.at(3).c_str())));
    }
    else if (tokens.at(0).compare("f") == 0) {
      std::vector<int> vertexIndices;
      std::vector<int> normalIndices;
      for (int i = 1; i <= 3; i++) {
        token = tokens.at(i);
        size_t pos = 0;
        std::vector<int> indices;
        while ((pos = token.find("//")) != std::string::npos) {
          indices.push_back(atoi(token.substr(0, pos).c_str()));
          token.erase(0, pos + 2);
        }
        indices.push_back(atoi(token.substr(0, pos).c_str()));
        vertexIndices.push_back(indices.at(0) - 1);
        normalIndices.push_back(indices.at(1) - 1);
      }
      mesh.addFace(Face(vertexIndices, normalIndices));
    }
  }
  
  return mesh;
}
