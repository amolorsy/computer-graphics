#include "swept_surface.h"
#include "trackball.h"
#include "data.h"

Trackball *trackball;
Camera *camera;
Data *data;

int width, height;
bool isLeftButtonPressed;

vector<glm::vec2> spline(int type, std::vector<ControlPoint> controlPoints, int steps) {
  vector<glm::vec2> points;

  for (int i = 0; i < controlPoints.size() - 3; i++) {
    for (int j = 0; j < steps; j++) {
      float t = (float) j / steps;
      float U[4] = { t * t * t, t * t, t, 1.0f };
      float G_x[4] = {
        controlPoints.at(i).getX(),
        controlPoints.at(i + 1).getX(),
        controlPoints.at(i + 2).getX(),
        controlPoints.at(i + 3).getX()
      };
      float G_y[4] = {
        controlPoints.at(i).getY(),
        controlPoints.at(i + 1).getY(),
        controlPoints.at(i + 2).getY(),
        controlPoints.at(i + 3).getY()
      };
      
      if (type == B_SPLINE)
        points.push_back(glm::vec2(b_spline_polynomial(U, G_x), b_spline_polynomial(U, G_y)));
      else if (type == CATMULL_ROM_SPLINE)
        points.push_back(glm::vec2(catmull_rom_spline_polynomial(U, G_x), catmull_rom_spline_polynomial(U, G_y)));
    }
  }
  return points;
}

void glutDisplay() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMultMatrixf(glm::value_ptr(camera->calculateProjectionMatrix()));

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glMultMatrixf(glm::value_ptr(camera->calculateViewMatrix()));
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
      delete data;
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
      camera->showAll();
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
  data = new Data();
  data->parse(argv[1]);
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  
  glutInitWindowSize(550, 550);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Swept Surface 3D Viewer");

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
