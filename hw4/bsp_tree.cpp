#include "bsp_tree.h"

BspTree::BspTree() {  
}

BspTree::~BspTree() {
  delete mRoot;
}

void BspTree::setRoot(BspNode* root) {
  mRoot = root;
}

BspNode* BspTree::getRoot() {
  return mRoot;
}

BspTree* BspTree::fromMesh(Mesh& mesh) {
  std::vector<Face> polygons = mesh.getFaces();
  
  BspTree* tree = new BspTree();
  tree->setRoot(BspTree::construct(mesh, polygons));
  return tree;
}

int BspTree::classifyVertex(glm::vec3 v, glm::vec3 p, glm::vec3 n) {
  float d = glm::dot(n, v - p);

  if (d > BspTree::EPSILON) return BspTree::VERTEX_FRONT;
  else if (d < -BspTree::EPSILON) return BspTree::VERTEX_BACK;
  else return BspTree::VERTEX_ON;
}

int BspTree::classifyPolygon(std::vector<glm::vec3> polygon, glm::vec3 p, glm::vec3 n) {
  int front = 0, back = 0, coplanar = 0;
  
  std::vector<float> ds;
  ds.push_back(glm::dot(n, polygon.at(0) - p));
  ds.push_back(glm::dot(n, polygon.at(1) - p));
  ds.push_back(glm::dot(n, polygon.at(2) - p));

  for (int i = 0; i < 3; i++) {
    float d = ds.at(i);
    if (d > BspTree::EPSILON) front++;
    else if (d < -BspTree::EPSILON) back++;
    else coplanar++;
  }

  if (coplanar == 3)
    return BspTree::POLYGON_COPLANAR;
  else if (coplanar == 2) {
    if (front == 1) return BspTree::POLYGON_FRONT;
    else return BspTree::POLYGON_BACK;
  }
  else if (coplanar == 1) {
    if (front == 2) return BspTree::POLYGON_FRONT;
    else if (front == 1) return BspTree::POLYGON_SPANNED_1;
    else return BspTree::POLYGON_BACK;
  }
  else {
    if (front == 3) return BspTree::POLYGON_FRONT;
    else if (front == 2 || front == 1) return BspTree::POLYGON_SPANNED_2;
    else return BspTree::POLYGON_BACK;
  }
}

BspNode* BspTree::construct(Mesh& mesh, std::vector<Face> polygons) {
  if (polygons.size() == 0) return NULL;
  
  std::vector<glm::vec3> vertices = mesh.getVertices();
  std::vector<glm::vec3> normals = mesh.getNormals();
  
  BspNode *node = new BspNode();
  int standard = rand() % polygons.size();
  Face plane = polygons.at(standard);  

  std::vector<int> sVIs = plane.getVertexIndices();
  std::vector<glm::vec3> sVs;
  sVs.push_back(vertices.at(sVIs.at(0)));
  sVs.push_back(vertices.at(sVIs.at(1)));
  sVs.push_back(vertices.at(sVIs.at(2)));
  glm::vec3 p = sVs.at(0);
  glm::vec3 n = glm::cross(sVs.at(1) - p, sVs.at(2) - p); 

  for (int i = 0; i < polygons.size(); i++) {
    if (i == standard) continue;
    
    Face polygon = polygons.at(i);
    std::vector<int> vIs = polygon.getVertexIndices();
    std::vector<int> nIs = polygon.getNormalIndices();
    std::vector<glm::vec3> vs;
    std::vector<glm::vec3> ns;
    vs.push_back(vertices.at(vIs.at(0)));
    vs.push_back(vertices.at(vIs.at(1)));
    vs.push_back(vertices.at(vIs.at(2)));
    ns.push_back(normals.at(nIs.at(0)));
    ns.push_back(normals.at(nIs.at(1)));
    ns.push_back(normals.at(nIs.at(2)));

    int polygonType = classifyPolygon(vs, p, n);
    if (polygonType == BspTree::POLYGON_COPLANAR)
      node->frontPolygons.push_back(polygon);
    else if (polygonType == BspTree::POLYGON_FRONT)
      node->frontPolygons.push_back(polygon);
    else if (polygonType == BspTree::POLYGON_BACK)
      node->backPolygons.push_back(polygon);
    else if (polygonType == BspTree::POLYGON_SPANNED_1) {
      // plane and face are intersect, one vertex is on plane
      int iA, iB, iC;
      for (int j = 0; j < 3; j++) {
        iA = j;
        if (BspTree::classifyVertex(vs.at(iA), p, n) == BspTree::VERTEX_ON) {
          iB = (iA + 1) % 3, iC = (iB + 1) % 3; 
          break;
        }
      }

      glm::vec3 vA = vs.at(iA), vB = vs.at(iB), vC = vs.at(iC);
      glm::vec3 nA = ns.at(iA), nB = ns.at(iB), nC = ns.at(iC);
      float t = glm::dot(n, p - vB) / glm::dot(n, vC - vB);
      mesh.addVertex((1.0f - t) * vB + t * vC);
      mesh.addNormal((1.0f - t) * nB + t * nC);
      int lastVertexIndex = mesh.getVertices().size() - 1;
      int lastNormalIndex = mesh.getNormals().size() - 1;
      
      std::vector<int> vIs1, vIs2, nIs1, nIs2;
      vIs1.push_back(vIs.at(iA));
      vIs1.push_back(vIs.at(iB));
      vIs1.push_back(lastVertexIndex);
      vIs2.push_back(vIs.at(iC));
      vIs2.push_back(vIs.at(iA));
      vIs2.push_back(lastVertexIndex);
      nIs1.push_back(nIs.at(iA));
      nIs1.push_back(nIs.at(iB));
      nIs1.push_back(lastNormalIndex);
      nIs2.push_back(nIs.at(iC));
      nIs2.push_back(nIs.at(iA));
      nIs2.push_back(lastNormalIndex);
  
      polygon.setVertexIndices(vIs1);
      polygon.setNormalIndices(nIs1);
      Face newPolygon(vIs2, nIs2);
      newPolygon.setMaterialIndex(polygon.getMaterialIndex());
      mesh.addFace(newPolygon);

      if (BspTree::classifyVertex(vB, p, n) == BspTree::VERTEX_FRONT
          && BspTree::classifyVertex(vC, p, n) == BspTree::VERTEX_BACK) {
        node->frontPolygons.push_back(polygon);
        node->backPolygons.push_back(newPolygon);
      }
      else { 
        node->backPolygons.push_back(polygon);
        node->frontPolygons.push_back(newPolygon);
      }
    }
    else {
      // plane and face are intersect, no vertex is on plane
      int iA, iB, iC;
      for (int j = 0; j < 3; j++) {
        iA = j, iB = (iA + 1) % 3;
        if (BspTree::classifyVertex(vs.at(iA), p, n) == BspTree::classifyVertex(vs.at(iB), p, n)) {
          iC = (iB + 1) % 3;
          break;
        }
      }

      glm::vec3 vA = vs.at(iA), vB = vs.at(iB), vC = vs.at(iC);
      glm::vec3 nA = ns.at(iA), nB = ns.at(iB), nC = ns.at(iC);
      float t1 = glm::dot(n, p - vC) / glm::dot(n, vA - vC);
      float t2 = glm::dot(n, p - vC) / glm::dot(n, vB - vC);
      mesh.addVertex((1.0f - t1) * vC + t1 * vA);
      mesh.addNormal((1.0f - t1) * nC + t1 * nA);
      mesh.addVertex((1.0f - t2) * vC + t2 * vB);
      mesh.addNormal((1.0f - t2) * nC + t2 * nB);
      int lastVertexIndex = mesh.getVertices().size() - 1;
      int lastNormalIndex = mesh.getNormals().size() - 1;
    
      std::vector<int> vIs1, vIs2, vIs3, nIs1, nIs2, nIs3;
      vIs1.push_back(vIs.at(iC));
      vIs1.push_back(lastVertexIndex - 1);
      vIs1.push_back(lastVertexIndex);
      vIs2.push_back(vIs.at(iA));
      vIs2.push_back(vIs.at(iB));
      vIs2.push_back(lastVertexIndex - 1);
      vIs3.push_back(vIs.at(iB));
      vIs3.push_back(lastVertexIndex);
      vIs3.push_back(lastVertexIndex - 1); 
      nIs1.push_back(nIs.at(iC));
      nIs1.push_back(lastNormalIndex - 1);
      nIs1.push_back(lastNormalIndex);
      nIs2.push_back(nIs.at(iA));
      nIs2.push_back(nIs.at(iB));
      nIs2.push_back(lastNormalIndex - 1);
      nIs3.push_back(nIs.at(iB));
      nIs3.push_back(lastNormalIndex);
      nIs3.push_back(lastNormalIndex - 1);

      polygon.setVertexIndices(vIs1);
      polygon.setNormalIndices(nIs1);
      Face newPolygon1(vIs2, nIs2);
      Face newPolygon2(vIs3, nIs3);
      newPolygon1.setMaterialIndex(polygon.getMaterialIndex());
      newPolygon2.setMaterialIndex(polygon.getMaterialIndex());
      mesh.addFace(newPolygon1);
      mesh.addFace(newPolygon2);
      
      if (BspTree::classifyVertex(vC, p, n) == BspTree::VERTEX_FRONT) {
        node->frontPolygons.push_back(polygon);
        node->backPolygons.push_back(newPolygon1);
        node->backPolygons.push_back(newPolygon2);
      }
      else {
        node->backPolygons.push_back(polygon);
        node->frontPolygons.push_back(newPolygon1);
        node->frontPolygons.push_back(newPolygon2);
      } 
    }
  }

  node->plane = plane;
  node->backChild = BspTree::construct(mesh, node->backPolygons);
  node->frontChild = BspTree::construct(mesh, node->frontPolygons);
  return node;
}
