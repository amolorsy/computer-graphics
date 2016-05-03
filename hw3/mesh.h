#include <vector>

#include "glm-0.9.7.4/glm/glm.hpp"

#include "face.h"

class Mesh {
  private:
    std::vector<glm::vec3> mVertices;
    std::vector<Face> mFaces;

  public:
    Mesh();
    ~Mesh();

    void addVertex(glm::vec3 vertex);
    void addFace(Face face);

    std::vector<glm::vec3> getVertices();
    std::vector<Face> getFaces();

    void clearVertices();
    void clearFaces();
};
