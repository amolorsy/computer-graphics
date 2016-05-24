#ifndef BSP_NODE_H
#define BSP_NODE_H

#include "glm-0.9.7.4/glm/glm.hpp"

#include "face.h"

class BspNode {
  public:
    Face plane;
    BspNode* frontChild;
    BspNode* backChild;
    std::vector<Face> frontPolygons;
    std::vector<Face> backPolygons;

    BspNode();
    ~BspNode();
};

#endif
