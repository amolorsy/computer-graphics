#include <vector>

class Face {
  private:
    std::vector<int> mVertexIndices;
    std::vector<int> mNormalIndices;

  public:
    Face(std::vector<int> mVertexIndices, std::vector<int> mNormalIndices);
    ~Face();

    std::vector<int> getVertexIndices();
    std::vector<int> getNormalIndices();
};
