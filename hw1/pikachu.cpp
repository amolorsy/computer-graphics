#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#include <algorithm>

const float RADIAN = M_PI / 180;
const float TIME_INTERVAL = 30;

const GLfloat AMBIENT_LIGHT[] = { 0.1f, 0.1f, 0.0f, 1.0f };
const GLfloat DIFFUSE_LIGHT[] = { 1.0f, 1.0f, 0.0f, 1.0f };
const GLfloat SPECULAR_LIGHT[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat LIGHT_POSITION[] = { -100.0f, 125.0f, 100.0f, 1.0f };

const GLfloat AMBIENT_SUB_LIGHT[] = { 0.3f, 0.3f, 0.3f, 1.0f };
const GLfloat DIFFUSE_SUB_LIGHT[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat SUB_LIGHT_POSITION[] = { 5.0f, 2.0f, -5.0f, 1.0f };

const GLfloat MATERIAL_AMBIENT[] = { 0.0f, 0.75f, 0.0f, 1.0f };
const GLfloat MATERIAL_SPECULAR[] = { 1.0f, 1.0f, 1.0f, 1.0f };

/* Vectors that makes the rotation and translation of the cube */
float eye[3] = { 20.0f, 0.0f, 100.0f };
float ref[3] = { 0.0f, 0.0f, 0.0f };
float rot[3] = { 0.0f, 0.0f, 0.0f };
/* End */

float bodyRot = 0.0f;
float headRot = 0.0f;
float tailRot = 0.0f;
float armRot = 0.0f;
float leftLegRot = 0.0f;
float rightLegRot = 0.0f;
float earRot = 0.0f;
float baseRot = 0.0f; // For debug

float loc = 0.0f;

float isLeftRaising = true, isRightRaising = true;
float isArmRaising = true, isTailRaising = true, isEarRaising = true;

int width, height;

void loadGlobalCoord() {
  glLoadIdentity();
  gluLookAt(eye[0], eye[1], eye[2], ref[0], ref[1], ref[2], 0, 1, 0);
}

void drawHemisphere(int xUnit, int yUnit, GLfloat r, bool isUpper) {
  if (!isUpper) {
    glRotatef(180, 1, 0, 0);
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

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  loadGlobalCoord();

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

  glTranslatef(0, 0, loc);
  glRotatef(baseRot, 0, 1, 0);
  glRotatef(bodyRot, 0, 0, 1);

  glColor3f(1.0, 1.0, 0); // Yellow color
  glRotatef(90.0f, 1, 0, 0);
  GLUquadricObj* body = gluNewQuadric();
  gluCylinder(body, 5.5, 7.0, 17, 100, 10);
  gluDeleteQuadric(body);

  GLUquadricObj* arm = gluNewQuadric();
  glPushMatrix();
    glRotatef(armRot, 0, 0, 1);
    glTranslatef(-4.0f, 3.0f, 10.0f);
    glRotatef(10.0f, 0, 1, 0);
    glRotatef(-60.0f, 1, 0, 0);
    gluCylinder(arm, 1.5, 0.75, 6, 100, 10);
  glPopMatrix();

  glPushMatrix();
    glRotatef(-armRot, 0, 0, 1);
    glTranslatef(4.0f, 3.0f, 10.0f);
    glRotatef(-10.0f, 0, 1, 0);
    glRotatef(-60.0f, 1, 0, 0);
    gluCylinder(arm, 1.5, 0.75, 6, 100, 10);
  glPopMatrix();
  gluDeleteQuadric(arm);
  
  GLUquadricObj* leg = gluNewQuadric();
  glPushMatrix();
    glRotatef(leftLegRot, 1, 0, 0);
    glRotatef(-15.0f, 0, 1, 0);
    glTranslatef(0.5f, 3.0f, 15.0f);
    gluCylinder(leg, 0.5, 1.75, 5, 100, 10);
  glPopMatrix();

  glPushMatrix();
    glRotatef(rightLegRot, 1, 0, 0);
    glRotatef(15.0f, 0, 1, 0);
    glTranslatef(-0.5f, 3.0f, 15.0f);
    gluCylinder(leg, 0.5, 1.75, 5, 100, 10);
  glPopMatrix();
  gluDeleteQuadric(leg);

  glPushMatrix();
    glTranslatef(4.0f, -12.0f, 0.0f);
    glRotatef(25.0f, 0, 0, 1);
    glRotatef(-35.0f + tailRot, 0, 1, 0); 
    glRotatef(-135.0f + tailRot, 1, 0, 0);
    glBegin(GL_TRIANGLE_STRIP);  
      glVertex3f(19, 8, 0);
      glVertex3f(12, 9, 0);
      glVertex3f(10, -2, 0);

      glVertex3f(10, -2, 0);
      glVertex3f(5, -4, 0);
      glVertex3f(12, 9, 0);

      glVertex3f(10, -2, 0);
      glVertex3f(5, -4, 0);
      glVertex3f(9, -4, 0);

      glVertex3f(10, -2, 0);
      glVertex3f(9, -4, 0);
      glVertex3f(13, -3, 0);

      glVertex3f(9, -4, 0);
      glVertex3f(13, -3, 0);
      glVertex3f(9, -8, 0);

      glVertex3f(9, -4, 0);
      glVertex3f(9, -8, 0);
      glVertex3f(5, -10, 0);

      glVertex3f(9, -8, 0);
      glVertex3f(5, -10, 0);
      glVertex3f(10, -11, 0);

      glVertex3f(9, -8, 0);
      glVertex3f(10, -11, 0);
      glVertex3f(14, -9, 0);
   
      glColor3ub(70, 12, 17); // Dark brown color

      glVertex3f(10, -11, 0);
      glVertex3f(14, -9, 0);
      glVertex3f(10, -15, 0);

      glVertex3f(10, -11, 0);
      glVertex3f(10, -15, 0);
      glVertex3f(8, -13, 0);  
    glEnd();

    glPushMatrix();
      glTranslatef(10.0f, 10.0f, 5.5f);
      glRotatef(20.0f, 1, 0, 0);
      glRotatef(180.0f, 0, 1, 0);
      glColor3f(1.0f, 0.0f, 0.0f);
      drawHemisphere(20, 20, 7, true);
      glColor3f(1.0f, 1.0f, 1.0f);
      drawHemisphere(20, 20, 7, false);
    
      glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);   
        glRotatef(90.0f, 1.0, 0.0, 0.0);
        GLUquadricObj* ring = gluNewQuadric();
        gluCylinder(ring, 7, 7, 1.5, 100, 10);
        gluDeleteQuadric(ring);
      glPopMatrix();

      glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
          for (int i = 0; i < 360; i++) {
            float angle = i * RADIAN;
            glVertex3f(cos(angle) * 3, sin(angle) * 3, 7.0f);
          }
        glEnd();
  
        glPushMatrix();
          glColor3f(1.0, 1.0, 1.0);
          glBegin(GL_POLYGON);
            for (int i = 0; i < 360; i++) {
              float angle = i * RADIAN;
              glVertex3f(cos(angle) * 2, sin(angle) * 2, 7.5f);
            }
          glEnd();
        glPopMatrix();
      glPopMatrix();
    glPopMatrix();
  glPopMatrix();

  glPushMatrix();
    glRotatef(headRot, 0, 1, 1);
    glColor3f(1.0, 1.0, 0);
    glTranslatef(0.0f, 1.5f, 1.5f);
    glRotatef(-90.0f, 1, 0, 0);
    GLUquadricObj* head = gluNewQuadric();                                                   
    gluSphere(head, 7.5, 100, 20); 
    gluDeleteQuadric(head);

    GLUquadricObj* eye = gluNewQuadric();
    glPushMatrix();
      glColor3f(0, 0, 0);
      glTranslatef(-3.5, 1.5, 6);
      gluSphere(eye, 1.25, 100, 20);
    glPopMatrix();

    glPushMatrix();
      glColor3f(0, 0, 0);
      glTranslatef(3.5, 1.5, 6);
      gluSphere(eye, 1.25, 100, 20);
    glPopMatrix();
    gluDeleteQuadric(eye);

    GLUquadricObj* cheek = gluNewQuadric();
    glPushMatrix();
      glColor3f(1, 0.35, 0.35);
      glTranslatef(-5, -2, 4.0);
      gluSphere(cheek, 1.5, 100, 20);
    glPopMatrix();

    glPushMatrix();
      glColor3f(1, 0.35, 0.35);
      glTranslatef(5, -2, 4.0);
      gluSphere(cheek, 1.5, 100, 20);
    glPopMatrix();
    gluDeleteQuadric(cheek);

    glPushMatrix();
      glTranslatef(0, -2.5, 0);
      glBegin(GL_LINE_STRIP);
        glColor3f(0, 0, 0);
        glVertex3f(-2, 0, 7);
        glVertex3f(-1, -0.5, 7);
        glVertex3f(0, 0, 7);
        glVertex3f(1, -0.5, 7);
        glVertex3f(2, 0, 7);
      glEnd();
    glPopMatrix();

    GLUquadricObj* ear = gluNewQuadric();
    glPushMatrix();
      glRotatef(earRot, 0, 0, 1);
      glRotatef(-90.0f, 1, 0, 0);
      glRotatef(-9.0f, 0, 1, 0);
      glTranslatef(-4.0, 0, 5);
      glColor3f(1.0, 1.0, 1.0);
      gluCylinder(ear, 1.0, 1.0, 6, 100, 20);
      
      glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslatef(0, 0, 6);
        glutSolidCone(1.0, 2, 100, 10);
      glPopMatrix();
    glPopMatrix();

    glPushMatrix();
      glRotatef(earRot, 0, 0, 1);
      glRotatef(-90.0f, 1, 0, 0);
      glRotatef(9.0f, 0, 1, 0);
      glTranslatef(4.0, 0, 5);
      glColor3f(1.0, 1.0, 1.0);
      gluCylinder(ear, 1.0, 1.0, 6, 100, 20);
        
      glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslatef(0, 0, 6);
        glutSolidCone(1.0, 2, 100, 10);
        glPopMatrix();
      glPopMatrix();
    glPopMatrix();
    gluDeleteQuadric(ear);
  glPopMatrix();
  
  glutSwapBuffers();
}

void resize(int w, int h) {
  if (w == 0 || h == 0) return;

  width = w;
  height = h;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f, (GLfloat) w / (GLfloat) h, .1f, 500.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void keyPress(unsigned char key, int x, int y) {
  switch (key) {
    case 27:
      exit(0);
      break;
    case 'w':
      if (headRot > -15.0f) headRot -= 1.0;
      if (tailRot < 15.0f) tailRot += 1.0;
      if (armRot < 15.0f) armRot += 1.0;
      break;
    case 's':
      if (headRot < 0.0f) headRot += 1.0;
      if (tailRot > 0.0f) tailRot -= 1.0;
      if (armRot > 0.0f) armRot -= 1.0;
      break;
    case 'a':
      if (loc < 25.0f) loc += 0.25;
      if (headRot < 0.0f) headRot += 1.0;
      if (leftLegRot == 8.0f) isLeftRaising = false;
      else if (leftLegRot == -8.0f) isLeftRaising = true;
      if (armRot >= 7.0f) isArmRaising = false;
      else if (armRot <= 0.0f) isArmRaising = true;
      if (tailRot >= 5.0f) isTailRaising = false;
      else if (tailRot <= 0.0f) isTailRaising = true;
      if (earRot >= 3.0f) isEarRaising = false;
      else if (earRot <= 0.0f) isEarRaising = true;
      leftLegRot += isLeftRaising ? 1.0f : -1.0f;
      rightLegRot = -leftLegRot;
      armRot += isArmRaising ? 0.25f : -0.25f;
      tailRot += isTailRaising ? 0.5f : -0.5f;
      earRot += isEarRaising ? 0.25f : -0.25f;
      break;
    case 'd':
      if (loc > 0.0f) loc -= 0.25;
      if (headRot < 0.0f) headRot += 1.0;
      if (leftLegRot == 8.0f) isLeftRaising = false;
      else if (leftLegRot == -8.0f) isLeftRaising = true;
      if (armRot >= 7.0f) isArmRaising = false;
      else if (armRot <= 0.0f) isArmRaising = true;
      if (tailRot >= 5.0f) isTailRaising = false;
      else if (tailRot <= 0.0f) isTailRaising = true;
      if (earRot >= 3.0f) isEarRaising = false;
      else if (earRot <= 0.0f) isEarRaising = true;
      leftLegRot += isLeftRaising ? 1.0f : -1.0f;
      rightLegRot = -leftLegRot;
      armRot += isArmRaising ? 0.25f : -0.25f;
      tailRot += isTailRaising ? 0.5f : -0.5f;
      earRot += isEarRaising ? 0.25f : -0.25f;
      break;
    case 'x':
      baseRot -= 1.0;
      break;
    default:
      break;
  }
}

void timer(int unused) {
  glutPostRedisplay();
  glutTimerFunc(TIME_INTERVAL, timer, 0);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(0, 0);
  
  glutCreateWindow("Pikachu");

  glutReshapeFunc(resize);
  glutDisplayFunc(display);
  glutTimerFunc(TIME_INTERVAL, timer, 0);
  glutKeyboardFunc(keyPress);

  glutMainLoop();

  return 0;
}
