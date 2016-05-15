#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

#include "glm-0.9.7.4/glm/glm.hpp"

#include "string_extensions.h"
#include "face.h"

class Mesh {
  private:
    std::vector<glm::vec3> mVertices;
    std::vector<glm::vec3> mNormals;
    std::vector<Face> mFaces;

  public:
    Mesh();
    ~Mesh();

    void addVertex(glm::vec3 vertex);
    void addNormal(glm::vec3 normal);
    void addFace(Face face);

    std::vector<glm::vec3> getVertices();
    std::vector<glm::vec3> getNormals();
    std::vector<Face> getFaces();

    void clearVertices();
    void clearNormals();
    void clearFaces();

    static Mesh fromObjFile(std::string filePath);
};
