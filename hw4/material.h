#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/gl.h>

class Material {
  private:
    GLfloat* mAmbient;
    GLfloat* mDiffuse;
    GLfloat* mSpecular;
    GLfloat mShininess;
  
  public:
    const static int RED_RUBBER = 0;
    const static int RUBY = 1;
    const static int JADE = 2;
    const static int CHROME = 3;
    const static int BRONZE = 4;
    const static int COPPER = 5;
    const static int CYAN_PLASTIC = 6;
    const static int PEARL = 7;

    Material(GLfloat ambient[], GLfloat diffuse[], GLfloat specular[], GLfloat shininess);
    ~Material();

    GLfloat* getAmbient();
    GLfloat* getDiffuse();
    GLfloat* getSpecular();
    GLfloat getShininess();

    static Material load(int materialIndex);
};

#endif
