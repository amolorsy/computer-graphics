#ifndef FACE_H
#define FACE_H

#include <vector>

class Face {
  private:
    int mMaterialIndex;
    std::vector<int> mVertexIndices;
    std::vector<int> mNormalIndices;

  public:
    Face();
    Face(std::vector<int> mVertexIndices, std::vector<int> mNormalIndices);
    ~Face();

    void setMaterialIndex(int materialIndex);
    int getMaterialIndex();

    void setVertexIndices(std::vector<int> vertexIndices);
    void setNormalIndices(std::vector<int> normalIndices);

    std::vector<int> getVertexIndices();
    std::vector<int> getNormalIndices();
};

#endif
