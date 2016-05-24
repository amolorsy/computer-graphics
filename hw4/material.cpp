#include "material.h"
#include <iostream>

Material::Material(GLfloat ambient[], GLfloat diffuse[], GLfloat specular[], GLfloat shininess) {
  mAmbient = ambient;
  mDiffuse = diffuse;
  mSpecular = specular;
  mShininess = shininess;
}

Material::~Material() {
}

GLfloat* Material::getAmbient() {
  return mAmbient;
}

GLfloat* Material::getDiffuse() {
  return mDiffuse;
}

GLfloat* Material::getSpecular() {
  return mSpecular;
}

GLfloat Material::getShininess() {
  return mShininess;
}

Material Material::load(int materialIndex) { 
  if (materialIndex == RED_RUBBER) {
    GLfloat ambient[] = {0.05f, 0.0f, 0.0f, 1.0f};
    GLfloat diffuse[] = {0.5f, 0.4f, 0.4f, 1.0f};
    GLfloat specular[] = {0.7f, 0.04f, 0.04f, 1.0f};
    GLfloat shininess = 0.078125f * 128.0f;
    return Material(ambient, diffuse, specular, shininess);
  }
  else if (materialIndex == RUBY) {
    GLfloat ambient[] = {0.1745f, 0.01175f, 0.01175f, 0.55f};
    GLfloat diffuse[] = {0.61424f, 0.04136f, 0.04136f, 0.55f};
    GLfloat specular[] = {0.727811f, 0.626959f, 0.626959f, 0.55f};
    GLfloat shininess = 0.6f * 128.0f;
    return Material(ambient, diffuse, specular, shininess);
  }
  else if (materialIndex == JADE) {
    GLfloat ambient[] = {0.135f, 0.2225f, 0.1575f, 1.0f};
    GLfloat diffuse[] = {0.54f, 0.89f, 0.63f, 1.0f};
    GLfloat specular[] = {0.316228f, 0.316228f, 0.316228f, 1.0f};
    GLfloat shininess = 0.1f * 128.0f;
    return Material(ambient, diffuse, specular, shininess);
  }
  else if (materialIndex == CHROME) {
    GLfloat ambient[] = {0.25f, 0.25f, 0.25f, 1.0f};
    GLfloat diffuse[] = {0.4f, 0.4f, 0.4f, 1.0f};
    GLfloat specular[] = {0.774597f, 0.774597f, 0.774597f, 1.0f};
    GLfloat shininess = 0.6f * 128.0f;
    return Material(ambient, diffuse, specular, shininess);
  }
  else if (materialIndex == BRONZE) {
    GLfloat ambient[] = {0.2125f, 0.1275f, 0.054f, 1.0f};
    GLfloat diffuse[] = {0.714f, 0.4284f, 0.18144f, 1.0f};
    GLfloat specular[] = {0.393548f, 0.271906f, 0.166721f, 1.0f};
    GLfloat shininess = 0.2f * 128.0f;
    return Material(ambient, diffuse, specular, shininess);
  }
  else if (materialIndex == COPPER) {
    GLfloat ambient[] = {0.19125f, 0.0735f, 0.0225f, 1.0f};
    GLfloat diffuse[] = {0.7038f, 0.27048f, 0.0828f, 1.0f};
    GLfloat specular[] = {0.256777f, 0.137622f, 0.086014f, 1.0f};
    GLfloat shininess = 0.1f * 128.0f;
    return Material(ambient, diffuse, specular, shininess);
  }
  else if (materialIndex == CYAN_PLASTIC) {
    GLfloat ambient[] = {0.0f, 0.1f, 0.06f, 1.0f};
    GLfloat diffuse[] = {0.0f, 0.50980392f, 0.50980392f, 1.0f};
    GLfloat specular[] = {0.50196078f, 0.50196078f, 0.50196078f, 1.0f};
    GLfloat shininess = 0.25f * 128.0f;
    return Material(ambient, diffuse, specular, shininess);
  }
  else if (materialIndex == PEARL) {
   GLfloat ambient[] = {0.25f, 0.20725f, 0.20725f, 1.0f};
   GLfloat diffuse[] = {1.0f, 0.829f, 0.829f, 1.0f};
   GLfloat specular[] = {0.296648f, 0.296648f, 0.296648f, 1.0f};
   GLfloat shininess = 0.088f * 128.0f;
   return Material(ambient, diffuse, specular, shininess);
  }
}
