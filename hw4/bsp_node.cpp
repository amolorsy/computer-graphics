#include "bsp_node.h"

BspNode::BspNode() {
}

BspNode::~BspNode() { 
  delete frontChild;
  delete backChild;
}
