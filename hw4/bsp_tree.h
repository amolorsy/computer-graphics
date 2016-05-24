#ifndef BSP_TREE_H
#define BSP_TREE_H

#include "glm-0.9.7.4/glm/glm.hpp"
#include "glm-0.9.7.4/glm/gtc/constants.hpp"

#include "mesh.h"
#include "bsp_node.h"

class BspTree {
  private:
    BspNode* mRoot;

  public:
    BspTree();
    ~BspTree();

    static const float EPSILON = 1.19209 * 0.0000001;

    static const int VERTEX_ON = 0;
    static const int VERTEX_FRONT = 1;
    static const int VERTEX_BACK = -1;
    static const int POLYGON_COPLANAR = 2;
    static const int POLYGON_FRONT = 3;
    static const int POLYGON_BACK = 4;
    static const int POLYGON_SPANNED_1 = 5;
    static const int POLYGON_SPANNED_2 = 6;
    
    void setRoot(BspNode* root);
    BspNode* getRoot();
    
    static BspTree* fromMesh(Mesh& mesh);
    static int classifyVertex(glm::vec3 v, glm::vec3 p, glm::vec3 n);
    static int classifyPolygon(std::vector<glm::vec3> polygon, glm::vec3 p, glm::vec3 n);
    static BspNode* construct(Mesh& mesh, std::vector<Face> polygons);
};

#endif
