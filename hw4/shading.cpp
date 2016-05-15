#include "shading.h"

using namespace std;

Trackball *trackball;
Camera *camera;

int width, height;
bool isLeftButtonPressed;

vector<Mesh> surfaces;

void glutDisplay() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMultMatrixf(glm::value_ptr(camera->calculateProjectionMatrix()));
         
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glMultMatrixf(glm::value_ptr(camera->calculateViewMatrix()));

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);  
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  for (int i = 0; i < surfaces.size(); i++) {
    Mesh surface = surfaces.at(i);
    vector<Face> faces = surface.getFaces();
    vector<glm::vec3> vertices = surface.getVertices();
    vector<glm::vec3> normals = surface.getNormals();

    glBegin(GL_TRIANGLES);
    for (int j = 0; j < faces.size(); j++) {
      Face face = faces.at(j);
      vector<int> normalIndices = face.getNormalIndices();
      vector<int> vertexIndices = face.getVertexIndices();
      glm::vec3 n1 = normals.at(normalIndices.at(0));
      glm::vec3 n2 = normals.at(normalIndices.at(1));
      glm::vec3 n3 = normals.at(normalIndices.at(2));
      glm::vec3 v1 = vertices.at(vertexIndices.at(0));
      glm::vec3 v2 = vertices.at(vertexIndices.at(1));
      glm::vec3 v3 = vertices.at(vertexIndices.at(2));
      
      glNormal3f(n1.x, n1.y, n1.z);
      glVertex3f(v1.x, v1.y, v1.z);
      glNormal3f(n2.x, n2.y, n2.z);
      glVertex3f(v2.x, v2.y, v2.z);
      glNormal3f(n3.x, n3.y, n3.z);
      glVertex3f(v3.x, v3.y, v3.z);
    } 
    glEnd();
  }
  glutSwapBuffers();
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
      {
        vector<glm::vec3> points;
        for (int i = 0; i < surfaces.size(); i++) {
          vector<glm::vec3> vertices = surfaces.at(i).getVertices();
          for (int j = 0; j < vertices.size(); j++)
            points.push_back(vertices.at(j));
        }
        camera->showAll(points);
      }
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

void glutTimer(int unused) {
  glutPostRedisplay();
  glutTimerFunc(30.0f, glutTimer, 0);
}
      
int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  
  glutInitWindowSize(550, 550);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Swept Surface 3D Viewer");

  surfaces.push_back(Mesh::fromObjFile("./samples/bulb.obj"));
  surfaces.push_back(Mesh::fromObjFile("./samples/cube.obj"));

  trackball = new Trackball(550, 550);
  camera = new Camera(550, 550);
  trackball->setCamera(camera);

  glutReshapeFunc(glutReshape);
  glutDisplayFunc(glutDisplay);
  glutTimerFunc(30.0f, glutTimer, 0);
  glutKeyboardFunc(glutKeyboard);
  glutSpecialFunc(glutSpecial);
  glutMouseFunc(glutMouse);
  glutMotionFunc(glutMotion);

  glutMainLoop();

  return 0;
}
