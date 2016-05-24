#include "shading.h"

int width, height;
bool isLeftButtonPressed;

vector<glm::vec3> vertices;
Mesh bulb;
Mesh cube1, cube2, cube3;
Mesh tetrahedron1, tetrahedron2, tetrahedron3;
BspTree *tree;

Trackball* trackball;
Camera* camera;

void setMaterialAttributes(int materialIndex) {
  Material material = Material::load(materialIndex);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material.getAmbient());
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material.getDiffuse());
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material.getSpecular());
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.getShininess()); 
}

void drawElement(Mesh mesh) {
  vector<glm::vec3> vs = mesh.getVertices();
  vector<glm::vec3> ns = mesh.getNormals();
  vector<Face> fs = mesh.getFaces();
  
  glBegin(GL_TRIANGLES);
    for (int i = 0; i < fs.size(); i++) {
      Face face = fs.at(i);
      vector<int> vIs = face.getVertexIndices();
      vector<int> nIs = face.getNormalIndices();
      glm::vec3 v1 = vs.at(vIs.at(0));
      glm::vec3 v2 = vs.at(vIs.at(1));
      glm::vec3 v3 = vs.at(vIs.at(2));
      glm::vec3 n1 = ns.at(nIs.at(0));
      glm::vec3 n2 = ns.at(nIs.at(1));
      glm::vec3 n3 = ns.at(nIs.at(2));

      int materialIndex = face.getMaterialIndex();
      setMaterialAttributes(materialIndex);
      
      glNormal3f(n1.x, n1.y, n1.z);
      glVertex3f(v1.x, v1.y, v1.z);
      glNormal3f(n2.x, n2.y, n2.z);
      glVertex3f(v2.x, v2.y, v2.z);
      glNormal3f(n3.x, n3.y, n3.z);
      glVertex3f(v3.x, v3.y, v3.z);
    }
  glEnd();
}

void traverse(BspNode *node) {
  vector<glm::vec3> vs = cube1.getVertices();
  vector<glm::vec3> ns = cube1.getNormals();
  vector<int> vIs = node->plane.getVertexIndices();
  vector<int> nIs = node->plane.getNormalIndices(); 
  
  glm::vec3 v1 = vs.at(vIs.at(0));
  glm::vec3 v2 = vs.at(vIs.at(1));
  glm::vec3 v3 = vs.at(vIs.at(2));
  glm::vec3 n1 = ns.at(nIs.at(0));
  glm::vec3 n2 = ns.at(nIs.at(1));
  glm::vec3 n3 = ns.at(nIs.at(2));

  int materialIndex = node->plane.getMaterialIndex();
  setMaterialAttributes(materialIndex);

  glm::vec3 n = glm::cross(v2 - v1, v3 - v1);
  float d = glm::dot(n, camera->mEye - v1);
 
  if (d > 0.0f) {
    if (node->backChild != NULL) traverse(node->backChild);
    glNormal3f(n1.x, n1.y, n1.z);
    glVertex3f(v1.x, v1.y, v1.z);
    glNormal3f(n2.x, n2.y, n2.z);
    glVertex3f(v2.x, v2.y, v2.z);
    glNormal3f(n3.x, n3.y, n3.z);
    glVertex3f(v3.x, v3.y, v3.z);
    if (node->frontChild != NULL) traverse(node->frontChild);
  }
  else {
    if (node->frontChild != NULL) traverse(node->frontChild);
    glNormal3f(n1.x, n1.y, n1.z);
    glVertex3f(v1.x, v1.y, v1.z);
    glNormal3f(n2.x, n2.y, n2.z);
    glVertex3f(v2.x, v2.y, v2.z);
    glNormal3f(n3.x, n3.y, n3.z);
    glVertex3f(v3.x, v3.y, v3.z); 
    if (node->backChild != NULL) traverse(node->backChild);
  }
}

void glutDisplay() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMultMatrixf(glm::value_ptr(camera->calculateProjectionMatrix()));
         
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glMultMatrixf(glm::value_ptr(camera->calculateViewMatrix()));

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  drawElement(bulb);
  glBegin(GL_TRIANGLES);
    traverse(tree->getRoot());
  glEnd();
  drawElement(cube2);
  drawElement(cube3);
  drawElement(tetrahedron1);
  drawElement(tetrahedron2);
  drawElement(tetrahedron3);

  glutSwapBuffers();
  glutPostRedisplay();
}

void glutReshape(int w, int h) {
  if (w == 0 || h == 0) return;

  width = w;
  height = h;

  trackball->resize(w, h);
  camera->changeAspect((float) w / (float) h);
  glViewport(0, 0, w, h);
}

void glutKeyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 27:
      delete tree;
      delete trackball;
      delete camera;
      exit(0);
      break;
    case 'q':
      camera->dollyIn();
      break;
    case 'a':
      camera->dollyOut();
      break;
    case 'w':
      camera->zoomIn();
      break;
    case 's':
      camera->zoomOut();
      break;
    case 'e':
      camera->showAll(vertices);
      break;
    default:
      break;
  }
}

void glutSpecial(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      camera->pan(DIRECTION_UP);
      break;
    case GLUT_KEY_DOWN:
      camera->pan(DIRECTION_DOWN);
      break;
    case GLUT_KEY_LEFT:
      camera->pan(DIRECTION_LEFT);
      break;
    case GLUT_KEY_RIGHT:
      camera->pan(DIRECTION_RIGHT);
      break;
  }
}

void glutMouse(int button, int state, int x, int y) {
  int modifiers;
  
  if (button == GLUT_LEFT_BUTTON) {
    switch (state) {
      case GLUT_DOWN:
        modifiers = glutGetModifiers();
        if (modifiers && GLUT_ACTIVE_SHIFT) {
          camera->seek(x, y);
        }
        else {
          if (!isLeftButtonPressed) {
            isLeftButtonPressed = true;
            trackball->start(x, y);
          }
        }
        break;
      case GLUT_UP:
        isLeftButtonPressed = false;
        break;
    }
  }
}

void glutMotion(int x, int y) {
  if (isLeftButtonPressed) {
    trackball->stop(x, y);
  }
}

int main(int argc, char **argv) {
  vector<Mesh> meshes;
  bulb = Mesh::fromObjFile("./samples/bulb.obj");
  vector<Face> &fs = bulb.getFaces();
  for (int i = 0; i < fs.size(); i++)
    fs.at(i).setMaterialIndex(Material::PEARL);
  bulb.scale(0.4f);
  meshes.push_back(bulb);

  cube1 = Mesh::fromObjFile("./samples/cube.obj");
  vector<Face> &fs1 = cube1.getFaces();
  for (int i = 0; i < fs1.size(); i++)
    fs1.at(i).setMaterialIndex(Material::RUBY);
  cube1.scale(3.0f);
  meshes.push_back(cube1);

  cube2 = Mesh::fromObjFile("./samples/cube.obj");
  vector<Face> &fs2 = cube2.getFaces();
  for (int i = 0; i < fs2.size(); i++)
    fs2.at(i).setMaterialIndex(Material::RED_RUBBER);
  cube2.scale(1.7f);
  cube2.translate(glm::vec3(-21.0f, -18.0f, 5.0f));
  meshes.push_back(cube2);

  cube3 = Mesh::fromObjFile("./samples/cube.obj");
  vector<Face> &fs3 = cube3.getFaces();
  for (int i = 0; i < fs3.size(); i++)
    fs3.at(i).setMaterialIndex(Material::CHROME);
  cube3.scale(2.0f);
  cube3.translate(glm::vec3(27.0f, 15.0f, 6.0f));
  meshes.push_back(cube3);

  tetrahedron1 = Mesh::fromObjFile("./samples/tetrahedron.obj");
  vector<Face> &fs4 = tetrahedron1.getFaces();
  for (int i = 0; i < fs4.size(); i++)
    fs4.at(i).setMaterialIndex(Material::COPPER);
  tetrahedron1.scale(9.0f);
  tetrahedron1.translate(glm::vec3(-35.0f, 3.0f, 3.0f));
  meshes.push_back(tetrahedron1);

  tetrahedron2 = Mesh::fromObjFile("./samples/tetrahedron.obj");
  vector<Face> &fs5 = tetrahedron2.getFaces();
  for (int i = 0; i < fs5.size(); i++)
    fs5.at(i).setMaterialIndex(Material::BRONZE);
  tetrahedron2.scale(12.0f);
  tetrahedron2.translate(glm::vec3(8.0f, -33.0f, -8.0f));
  meshes.push_back(tetrahedron2);

  tetrahedron3 = Mesh::fromObjFile("./samples/tetrahedron.obj");
  vector<Face> &fs6 = tetrahedron3.getFaces();
  for (int i = 0; i < fs6.size(); i++)
    fs6.at(i).setMaterialIndex(Material::CYAN_PLASTIC);
  tetrahedron3.scale(7.0f);
  tetrahedron3.translate(glm::vec3(-30.0f, -10.0f, 5.0f));
  meshes.push_back(tetrahedron3);

  vertices = Mesh::merge(meshes).getVertices();
  tree = BspTree::fromMesh(cube1);
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  
  glutInitWindowSize(800, 650);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Shading");

  trackball = new Trackball(800, 650);
  camera = new Camera(800, 650);
  trackball->setCamera(camera);

  glEnable(GL_LIGHTING);
 	glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_AMBIENT, AMBIENT_LIGHT);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, DIFFUSE_LIGHT);
  glLightfv(GL_LIGHT0, GL_SPECULAR, SPECULAR_LIGHT);
  glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_POSITION);
  glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, SPOT_CUTOFF);
  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, SPOT_DIRECTION);
  glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, SPOT_EXPONENT);
                                    
  glEnable(GL_LIGHT1);
  glLightfv(GL_LIGHT1, GL_AMBIENT, AMBIENT_SUB_LIGHT);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, DIFFUSE_SUB_LIGHT);
  glLightfv(GL_LIGHT1, GL_SPECULAR, SPECULAR_SUB_LIGHT);
  glLightfv(GL_LIGHT1, GL_POSITION, SUB_LIGHT_POSITION);

  glShadeModel(GL_SMOOTH);
  glEnable(GL_CULL_FACE);
  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glutReshapeFunc(glutReshape);
  glutDisplayFunc(glutDisplay);
  glutKeyboardFunc(glutKeyboard);
  glutSpecialFunc(glutSpecial);
  glutMouseFunc(glutMouse);
  glutMotionFunc(glutMotion);

  glutMainLoop();

  return 0;
}
