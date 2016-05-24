#ifndef TRACKBALL_H
#define TRACKBALL_H

#include <cmath>
#include <algorithm>

#include "glm-0.9.7.4/glm/glm.hpp"
#include "glm-0.9.7.4/glm/gtc/type_ptr.hpp"
#include "glm-0.9.7.4/glm/gtc/matrix_transform.hpp"
#include "glm-0.9.7.4/glm/gtx/rotate_vector.hpp"
#include "glm-0.9.7.4/glm/gtc/matrix_inverse.hpp"
#include "glm-0.9.7.4/glm/gtx/vector_angle.hpp"

#include "camera.h"

class Trackball {
  private:
    int mWidth, mHeight; // Window
    
    glm::vec3 mPrevPos;
    glm::vec3 mCurrPos;
    
    float mAngle;
    glm::vec3 mAxis;
    glm::mat4 mRotationMatrix;

    Camera *mCamera;

  public:
    Trackball(int width, int height);
    ~Trackball();

    void setCamera(Camera *camera);

    glm::mat4 calculateRotationMatrix();    

    void resize(int width, int height);
    glm::vec3 projectOntoHemisphere(int x, int y);
    void start(int x, int y);
    void stop(int x, int y);
};

#endif
