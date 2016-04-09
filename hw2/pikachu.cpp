#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include "trackball.h"

const GLfloat RADIAN = M_PI / 180.0f;
const GLfloat TIME_INTERVAL = 30.0f;

/* For light and material */
const GLfloat AMBIENT_LIGHT[] = { 0.1f, 0.1f, 0.0f, 1.0f };
const GLfloat DIFFUSE_LIGHT[] = { 1.0f, 1.0f, 0.0f, 1.0f };
const GLfloat SPECULAR_LIGHT[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat LIGHT_POSITION[] = { -100.0f, 125.0f, 100.0f, 1.0f };

const GLfloat AMBIENT_SUB_LIGHT[] = { 0.3f, 0.3f, 0.3f, 1.0f };
const GLfloat DIFFUSE_SUB_LIGHT[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat SUB_LIGHT_POSITION[] = { 7.0f, 0.0f, -5.0f, 1.0f };

const GLfloat MATERIAL_AMBIENT[] = { 0.0f, 0.75f, 0.0f, 1.0f };
const GLfloat MATERIAL_SPECULAR[] = { 1.0f, 1.0f, 1.0f, 1.0f };
/* End */

int width, height;

bool isLeftButtonPressed;
Trackball *trackball;
Camera *camera;

void drawHead() {
  glColor3f(1.0f, 1.0f, 0.0f);
  glTranslatef(0.0f, 1.5f, 1.5f);
  glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
  
  GLUquadricObj* head = gluNewQuadric();                                                   
  gluSphere(head, 7.5, 100, 20); 
  gluDeleteQuadric(head);
}

void drawLeftEye() {
  glColor3f(0.0f, 0.0f, 0.0f);
  glTranslatef(-3.5f, 1.5f, 6.0f);
    
  GLUquadricObj* eye = gluNewQuadric();
  gluSphere(eye, 1.25, 100, 20);
  gluDeleteQuadric(eye);
}

void drawRightEye() {
  glColor3f(0.0f, 0.0f, 0.0f);
  glTranslatef(3.5f, 1.5f, 6.0f);
  
  GLUquadricObj* eye = gluNewQuadric();
  gluSphere(eye, 1.25, 100, 20);
  gluDeleteQuadric(eye);
}

void drawLeftCheek() {
  glColor3f(1.0f, 0.35f, 0.35f);
  glTranslatef(-5.0f, -2.0f, 4.0f);
  
  GLUquadricObj* cheek = gluNewQuadric();
  gluSphere(cheek, 1.5, 100, 20);
  gluDeleteQuadric(cheek);
}

void drawRightCheek() {
  glColor3f(1.0f, 0.35f, 0.35f);
  glTranslatef(5.0f, -2.0f, 4.0f);
  
  GLUquadricObj* cheek = gluNewQuadric();
  gluSphere(cheek, 1.5, 100, 20);
  gluDeleteQuadric(cheek);
}

void drawMouse() {
  glColor3f(0.0f, 0.0f, 0.0f);
  glTranslatef(0.0f, -2.5f, 0.0f);
  
  glBegin(GL_LINE_STRIP);
    glVertex3f(-2.0f, 0.0f, 7.0f);
    glVertex3f(-1.0f, -0.5f, 7.0f);
    glVertex3f(0.0f, 0.0f, 7.0f);
    glVertex3f(1.0f, -0.5f, 7.0f);
    glVertex3f(2.0f, 0.0f, 7.0f);
  glEnd();
}

void drawLeftEar() {
  glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
  glRotatef(-9.0f, 0.0f, 1.0f, 0.0f);
  glTranslatef(-4.0f, 0.0f, 5.0f);
  glColor3f(1.0f, 1.0f, 1.0f);
 
  GLUquadricObj* ear = gluNewQuadric();
  gluCylinder(ear, 1.0, 1.0, 6.0, 100, 20);
      
  glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 6.0f);
    
    glutSolidCone(1.0, 2.0, 100, 10);
  glPopMatrix();

  gluDeleteQuadric(ear);
}

void drawRightEar() {
  glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
  glRotatef(9.0f, 0.0f, 1.0f, 0.0f);
  glTranslatef(4.0f, 0.0f, 5.0f);
  glColor3f(1.0f, 1.0f, 1.0f);
  
  GLUquadricObj* ear = gluNewQuadric();
  gluCylinder(ear, 1.0, 1.0, 6.0, 100, 20);
        
  glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 6.0f);
        
    glutSolidCone(1.0, 2.0, 100, 10);
  glPopMatrix();

  gluDeleteQuadric(ear);
}

void drawLeftArm() {
  glTranslatef(-4.0f, 3.0f, 10.0f);
  glRotatef(10.0f, 0.0f, 1.0f, 0.0f);
  glRotatef(-60.0f, 1.0f, 0.0f, 0.0f);
 
  GLUquadricObj* arm = gluNewQuadric();
  gluCylinder(arm, 1.5, 0.75, 6.0, 100, 10);
  gluDeleteQuadric(arm);
}

void drawRightArm() {
  glTranslatef(4.0f, 3.0f, 10.0f);
  glRotatef(-10.0f, 0.0f, 1.0f, 0.0f);
  glRotatef(-60.0f, 1.0f, 0.0f, 0.0f);
  
  GLUquadricObj* arm = gluNewQuadric();
  gluCylinder(arm, 1.5, 0.75, 6.0, 100, 10);
  gluDeleteQuadric(arm);
}

void drawLeftLeg() {
  glRotatef(-15.0f, 0.0f, 1.0f, 0.0f);
  glTranslatef(0.5f, 3.0f, 15.0f);
 
  GLUquadricObj* leg = gluNewQuadric();
  gluCylinder(leg, 0.5, 1.75, 5.0, 100, 10);
  gluDeleteQuadric(leg);
}

void drawRightLeg() {
  glRotatef(15.0f, 0.0f, 1.0f, 0.0f);
  glTranslatef(-0.5f, 3.0f, 15.0f);
  
  GLUquadricObj* leg = gluNewQuadric();
  gluCylinder(leg, 0.5, 1.75, 5.0, 100, 10);
  gluDeleteQuadric(leg);
}

void drawTail() {
  glTranslatef(4.0f, -12.0f, 0.0f);
  glRotatef(25.0f, 0.0f, 0.0f, 1.0f);
  glRotatef(-35.0f, 0.0f, 1.0f, 0.0f); 
  glRotatef(-135.0f, 1.0f, 0.0f, 0.0f);
  
  glBegin(GL_TRIANGLE_STRIP);  
    glVertex3f(19.0f, 8.0f, 0.0f);
    glVertex3f(12.0f, 9.0f, 0.0f);
    glVertex3f(10.0f, -2.0f, 0.0f);

    glVertex3f(10.0f, -2.0f, 0.0f);
    glVertex3f(5.0f, -4.0f, 0.0f);
    glVertex3f(12.0f, 9.0f, 0.0f);

    glVertex3f(10.0f, -2.0f, 0.0f);
    glVertex3f(5.0f, -4.0f, 0.0f);
    glVertex3f(9.0f, -4.0f, 0.0f);

    glVertex3f(10.0f, -2.0f, 0.0f);
    glVertex3f(9.0f, -4.0f, 0.0f);
    glVertex3f(13.0f, -3.0f, 0.0f);

    glVertex3f(9.0f, -4.0f, 0.0f);
    glVertex3f(13.0f, -3.0f, 0.0f);
    glVertex3f(9.0f, -8.0f, 0.0f);

    glVertex3f(9.0f, -4.0f, 0.0f);
    glVertex3f(9.0f, -8.0f, 0.0f);
    glVertex3f(5.0f, -10.0f, 0.0f);

    glVertex3f(9.0f, -8.0f, 0.0f);
    glVertex3f(5.0f, -10.0f, 0.0f);
    glVertex3f(10.0f, -11.0f, 0.0f);

    glVertex3f(9.0f, -8.0f, 0.0f);
    glVertex3f(10.0f, -11.0f, 0.0f);
    glVertex3f(14.0f, -9.0f, 0.0f);
   
    glColor3ub(70, 12, 17); // Dark brown color

    glVertex3f(10.0f, -11.0f, 0.0f);
    glVertex3f(14.0f, -9.0f, 0.0f);
    glVertex3f(10.0f, -15.0f, 0.0f);

    glVertex3f(10.0f, -11.0f, 0.0f);
    glVertex3f(10.0f, -15.0f, 0.0f);
    glVertex3f(8.0f, -13.0f, 0.0f);  
  glEnd();
}

void drawHemisphere(int xUnit, int yUnit, GLfloat r, bool isUpper) {
  if (!isUpper) {
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
  }
  
  GLfloat vertex[xUnit * yUnit][3];      
  for (int i = 0; i < xUnit; ++i) {
    for (int j = 0; j < yUnit; ++j) {
      vertex[i * yUnit + j][0]= r * cos(j * 2 * M_PI / yUnit) * cos(i * M_PI / (2 * xUnit));
      vertex[i * yUnit + j][1]= r * sin(i * M_PI / (2 * xUnit));
      vertex[i * yUnit + j][2]= r * sin(j * 2 * M_PI / yUnit) * cos(i * M_PI / (2 * xUnit));
    }
  }

  glBegin(GL_QUADS);
    for (int i = 0; i < xUnit - 1; ++i) {
      for (int j = 0; j < yUnit; ++j) {
        glVertex3fv(vertex[i * yUnit + j]);
        glVertex3fv(vertex[i * yUnit + (j + 1) % yUnit]);
        glVertex3fv(vertex[(i + 1) * yUnit + (j + 1) % yUnit]);
        glVertex3fv(vertex[(i + 1) * yUnit + j]);
      }
    }
  glEnd();
}

void drawBall() {
  glTranslatef(10.0f, 10.0f, 5.5f);
  glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
  glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
  
  glColor3f(1.0f, 0.0f, 0.0f);
  drawHemisphere(20, 20, 7.0f, true);
  glColor3f(1.0f, 1.0f, 1.0f);
  drawHemisphere(20, 20, 7.0f, false);
    
  glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);   
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    
    GLUquadricObj* ring = gluNewQuadric();
    gluCylinder(ring, 7.0, 7.0, 1.5, 100, 10);
    gluDeleteQuadric(ring);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    
    glBegin(GL_POLYGON);
      for (int i = 0; i < 360; i++) {
        float angle = i * RADIAN;
        glVertex3f(cos(angle) * 3, sin(angle) * 3, 7.0f);
      }
    glEnd();
  
    glPushMatrix();
      glColor3f(1.0f, 1.0f, 1.0f);
      
      glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i++) {
          float angle = i * RADIAN;
          glVertex3f(cos(angle) * 2, sin(angle) * 2, 7.5f);
        }
      glEnd();
    glPopMatrix();
  glPopMatrix();
}

void glutDisplay() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMultMatrixf(glm::value_ptr(camera->calculateProjectionMatrix()));
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glMultMatrixf(glm::value_ptr(
        camera->calculateViewMatrix()));

  glPushMatrix();
  glShadeModel(GL_SMOOTH);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
                      
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_AMBIENT, AMBIENT_LIGHT);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, DIFFUSE_LIGHT);
  glLightfv(GL_LIGHT0, GL_SPECULAR, SPECULAR_LIGHT);
  glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_POSITION);
                                    
  glEnable(GL_LIGHT1);
  glLightfv(GL_LIGHT1, GL_AMBIENT, AMBIENT_SUB_LIGHT);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, DIFFUSE_SUB_LIGHT);
  glLightfv(GL_LIGHT1, GL_SPECULAR, SPECULAR_LIGHT);
  glLightfv(GL_LIGHT1, GL_POSITION, SUB_LIGHT_POSITION);

  glEnable(GL_COLOR_MATERIAL); 
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, MATERIAL_AMBIENT); 
  glMaterialfv(GL_FRONT, GL_SPECULAR, MATERIAL_SPECULAR);
  glMateriali(GL_FRONT, GL_SHININESS, 48);

  glTranslatef(0.0f, 5.0f, 0.0f);
  glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
  glColor3f(1.0f, 1.0f, 0.0f); // Yellow color
  
  GLUquadricObj* body = gluNewQuadric();
  gluCylinder(body, 5.5, 7.0, 17.0, 100, 10);
  gluDeleteQuadric(body);

  glPushMatrix();
    drawLeftArm();
  glPopMatrix();

  glPushMatrix();
    drawRightArm();
  glPopMatrix();

  glPushMatrix();
    drawLeftLeg();
  glPopMatrix();

  glPushMatrix();
    drawRightLeg();
  glPopMatrix();
  
  glPushMatrix();
    drawTail();      
    
    glPushMatrix();
      drawBall();
    glPopMatrix();
  glPopMatrix();

  glPushMatrix();
    drawHead();  
 
    glPushMatrix();
      drawLeftEye();
    glPopMatrix();

    glPushMatrix();
      drawRightEye();
    glPopMatrix();

    glPushMatrix();
      drawLeftCheek();
    glPopMatrix();

    glPushMatrix();
      drawRightCheek();
    glPopMatrix();

    glPushMatrix();
      drawMouse();  
    glPopMatrix();

    glPushMatrix();
      drawLeftEar();
    glPopMatrix();

    glPushMatrix();
      drawRightEar();
    glPopMatrix();
  glPopMatrix();
  glPopMatrix();
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
  glutTimerFunc(TIME_INTERVAL, glutTimer, 0);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  
  glutInitWindowSize(550, 550);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Pikachu 3D Viewer");

  trackball = new Trackball(550, 550);
  camera = new Camera(550, 550);
  trackball->setCamera(camera);

  glutReshapeFunc(glutReshape);
  glutDisplayFunc(glutDisplay);
  glutTimerFunc(TIME_INTERVAL, glutTimer, 0);
  glutKeyboardFunc(glutKeyboard);
  glutSpecialFunc(glutSpecial);
  glutMouseFunc(glutMouse);
  glutMotionFunc(glutMotion);

  glutMainLoop();

  return 0;
}
