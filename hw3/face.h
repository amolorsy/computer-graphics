#include <vector>

class Face {
  private:
    std::vector<int> mIndices;

  public:
    Face(std::vector<int> indices);
    ~Face();

    std::vector<int> getIndices();
};
