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
const GLfloat SUB_LIGHT_POSITION[] = { 7.0f, 0.0f, -5.0f, 1.0f };

const GLfloat MATERIAL_AMBIENT[] = { 0.0f, 0.75f, 0.0f, 1.0f };
const GLfloat MATERIAL_SPECULAR[] = { 1.0f, 1.0f, 1.0f, 1.0f };

/* Vectors that makes the rotation and translation of the cube */
float eye[3] = { 25.0f, 0.0f, 100.0f };
float ref[3] = { 0.0f, 0.0f, 0.0f };
float rot[3] = { 0.0f, 0.0f, 0.0f };
/* End */

float baseTrans;
float bodyRot, headRot, tailRot, armsRot, earsRot;
float leftLegRot, rightLegRot;
float ballRot;

bool isHeadRaising, isEarRaising;
bool isLeftLegRaising, isRightLegRaising;
bool isArmRaising, isTailRaising;
bool isBallRaising;

bool isLeftButtonPressed;
float mousePosX, mousePosY;

int width, height;

void loadGlobalCoord() {
  glLoadIdentity();
  gluLookAt(eye[0], eye[1], eye[2], ref[0], ref[1], ref[2], 0, 1, 0);
}

void drawHead() {
  glRotatef(headRot, 0, 1, 1);
  glColor3f(1.0, 1.0, 0);
  glTranslatef(0.0f, 1.5f, 1.5f);
  glRotatef(-90.0f, 1, 0, 0);
  
  GLUquadricObj* head = gluNewQuadric();                                                   
  gluSphere(head, 7.5, 100, 20); 
  gluDeleteQuadric(head);
}

void drawLeftEye() {
  glColor3f(0, 0, 0);
  glTranslatef(-3.5, 1.5, 6);
    
  GLUquadricObj* eye = gluNewQuadric();
  gluSphere(eye, 1.25, 100, 20);
  gluDeleteQuadric(eye);
}

void drawRightEye() {
  glColor3f(0, 0, 0);
  glTranslatef(3.5, 1.5, 6);
  
  GLUquadricObj* eye = gluNewQuadric();
  gluSphere(eye, 1.25, 100, 20);
  gluDeleteQuadric(eye);
}

void drawLeftCheek() {
  glColor3f(1, 0.35, 0.35);
  glTranslatef(-5, -2, 4.0);
  
  GLUquadricObj* cheek = gluNewQuadric();
  gluSphere(cheek, 1.5, 100, 20);
  gluDeleteQuadric(cheek);
}

void drawRightCheek() {
  glColor3f(1, 0.35, 0.35);
  glTranslatef(5, -2, 4.0);
  
  GLUquadricObj* cheek = gluNewQuadric();
  gluSphere(cheek, 1.5, 100, 20);
  gluDeleteQuadric(cheek);
}

void drawMouse() {
  glColor3f(0, 0, 0);
  glTranslatef(0, -2.5, 0);
  
  glBegin(GL_LINE_STRIP);
    glVertex3f(-2, 0, 7);
    glVertex3f(-1, -0.5, 7);
    glVertex3f(0, 0, 7);
    glVertex3f(1, -0.5, 7);
    glVertex3f(2, 0, 7);
  glEnd();
}

void drawLeftEar() {
  glRotatef(earsRot, 0, 0, 1);
  glRotatef(-90.0f, 1, 0, 0);
  glRotatef(-9.0f, 0, 1, 0);
  glTranslatef(-4.0, 0, 5);
  glColor3f(1.0, 1.0, 1.0);
 
  GLUquadricObj* ear = gluNewQuadric();
  gluCylinder(ear, 1.0, 1.0, 6, 100, 20);
      
  glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(0, 0, 6);
    
    glutSolidCone(1.0, 2, 100, 10);
  glPopMatrix();

  gluDeleteQuadric(ear);
}

void drawRightEar() {
  glRotatef(earsRot, 0, 0, 1);
  glRotatef(-90.0f, 1, 0, 0);
  glRotatef(9.0f, 0, 1, 0);
  glTranslatef(4.0, 0, 5);
  glColor3f(1.0, 1.0, 1.0);
  
  GLUquadricObj* ear = gluNewQuadric();
  gluCylinder(ear, 1.0, 1.0, 6, 100, 20);
        
  glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(0, 0, 6);
        
    glutSolidCone(1.0, 2, 100, 10);
  glPopMatrix();

  gluDeleteQuadric(ear);
}

void drawLeftArm() {
  glRotatef(armsRot, 0, 0, 1);
  glTranslatef(-4.0f, 3.0f, 10.0f);
  glRotatef(10.0f, 0, 1, 0);
  glRotatef(-60.0f, 1, 0, 0);
 
  GLUquadricObj* arm = gluNewQuadric();
  gluCylinder(arm, 1.5, 0.75, 6, 100, 10);
  gluDeleteQuadric(arm);
}

void drawRightArm() {
  glRotatef(-armsRot, 0, 0, 1);
  glTranslatef(4.0f, 3.0f, 10.0f);
  glRotatef(-10.0f, 0, 1, 0);
  glRotatef(-60.0f, 1, 0, 0);
  
  GLUquadricObj* arm = gluNewQuadric();
  gluCylinder(arm, 1.5, 0.75, 6, 100, 10);
  gluDeleteQuadric(arm);
}

void drawLeftLeg() {
  glRotatef(leftLegRot, 1, 0, 0);
  glRotatef(-15.0f, 0, 1, 0);
  glTranslatef(0.5f, 3.0f, 15.0f);
 
  GLUquadricObj* leg = gluNewQuadric();
  gluCylinder(leg, 0.5, 1.75, 5, 100, 10);
  gluDeleteQuadric(leg);
}

void drawRightLeg() {
  glRotatef(rightLegRot, 1, 0, 0);
  glRotatef(15.0f, 0, 1, 0);
  glTranslatef(-0.5f, 3.0f, 15.0f);
  
  GLUquadricObj* leg = gluNewQuadric();
  gluCylinder(leg, 0.5, 1.75, 5, 100, 10);
  gluDeleteQuadric(leg);
}

void drawTail() {
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

void drawBall() {
  glTranslatef(10.0f, 10.0f, 5.5f);
  glRotatef(ballRot, 0, 0, 1);
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
}

void glutDisplay() {
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

  glTranslatef(0, 0, baseTrans);
  glRotatef(bodyRot, 0, 0, 1);
  glRotatef(90.0f, 1, 0, 0);
  glColor3f(1.0, 1.0, 0); // Yellow color
  
  GLUquadricObj* body = gluNewQuadric();
  gluCylinder(body, 5.5, 7.0, 17, 100, 10);
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
  
  glutSwapBuffers();
}

void glutReshape(int w, int h) {
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

void glutKeyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 27:
      exit(0);
      break;
    default:
      break;
  }
}

void glutSpecial(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      if (headRot > -15.0f) headRot -= 1.0;
      if (tailRot < 15.0f) tailRot += 1.0;
      if (armsRot < 20.0f) armsRot += 1.0;
      if (ballRot < 30.0f) ballRot += 1.5;
      break;
    case GLUT_KEY_DOWN:
      if (headRot < 0.0f) headRot += 1.0;
      if (tailRot > 0.0f) tailRot -= 1.0;
      if (armsRot > 0.0f) armsRot -= 1.0;
      if (ballRot > 0.0f) ballRot -= 1.5;
      break;
    case GLUT_KEY_LEFT:
      if (baseTrans < 25.0f) baseTrans += 0.25;
      if (headRot >= 3.0f) isHeadRaising = true;
      else if (headRot <= -3.0f) isHeadRaising = false;
      if (leftLegRot >= 10.0f) isLeftLegRaising = true;
      else if (leftLegRot <= -10.0f) isLeftLegRaising = false;
      if (armsRot >= 7.0f) isArmRaising = true;
      else if (armsRot <= 0.0f) isArmRaising = false;
      if (tailRot >= 5.0f) isTailRaising = true;
      else if (tailRot <= 0.0f) isTailRaising = false;
      if (earsRot >= 3.0f) isEarRaising = true;
      else if (earsRot <= 0.0f) isEarRaising = false;
      if (ballRot >= 50.0f) isBallRaising = true;
      else if (ballRot <= 0.0f) isBallRaising = false;
      headRot += isHeadRaising ? -0.5f : 0.5f;
      leftLegRot += isLeftLegRaising ? -1.0f : 1.0f;
      rightLegRot = -leftLegRot;
      armsRot += isArmRaising ? -0.5f : 0.5f;
      tailRot += isTailRaising ? -0.5f : 0.5f;
      earsRot += isEarRaising ? -0.25f : 0.25f;
      ballRot += isBallRaising ? -1.0f : 1.0f;
      break;
    case GLUT_KEY_RIGHT:
      if (baseTrans > -7.5f) baseTrans -= 0.25;
      if (headRot >= 3.0f) isHeadRaising = true;
      else if (headRot <= -3.0f) isHeadRaising = false;
      if (leftLegRot >= 10.0f) isLeftLegRaising = true;
      else if (leftLegRot <= -10.0f) isLeftLegRaising = false;
      if (armsRot >= 7.0f) isArmRaising = true;
      else if (armsRot <= 0.0f) isArmRaising = false;
      if (tailRot >= 5.0f) isTailRaising = true;
      else if (tailRot <= 0.0f) isTailRaising = false;
      if (earsRot >= 3.0f) isEarRaising = true;
      else if (earsRot <= 0.0f) isEarRaising = false;
      if (ballRot >= 50.0f) isBallRaising = true;
      else if (ballRot <= 0.0f) isBallRaising = false;
      headRot += isHeadRaising ? -0.5f : 0.5f;
      leftLegRot += isLeftLegRaising ? -1.0f : 1.0f;
      rightLegRot = -leftLegRot;
      armsRot += isArmRaising ? -0.5f : 0.5f;
      tailRot += isTailRaising ? -0.5f : 0.5f;
      earsRot += isEarRaising ? -0.25f : 0.25f;
      ballRot += isBallRaising ? -1.0f : 1.0f;
      break;
  }
}

void glutTimer(int unused) {
  glutPostRedisplay();
  glutTimerFunc(TIME_INTERVAL, glutTimer, 0);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(0, 0);
  
  glutCreateWindow("Pikachu");

  glutReshapeFunc(glutReshape);
  glutDisplayFunc(glutDisplay);
  glutTimerFunc(TIME_INTERVAL, glutTimer, 0);
  glutKeyboardFunc(glutKeyboard);
  glutSpecialFunc(glutSpecial);
  // glutMouseFunc(glutMouse);
  // glutMotionFunc(glutMotion);

  glutMainLoop();

  return 0;
}
