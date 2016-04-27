#include "trackball.h"

Trackball::Trackball(int width, int height) {
  mWidth = width;
  mHeight = height;
  
  mAngle = 0.0f;
  mAxis = glm::vec3(0.0f, 1.0f, 0.0f);
  mRotationMatrix = glm::mat4(1.0f);
}

Trackball::~Trackball() {
}

void Trackball::setCamera(Camera *camera) {
  mCamera = camera;
}

glm::mat4 Trackball::calculateRotationMatrix() {
  return mRotationMatrix;
}

void Trackball::resize(int width, int height) {
  mWidth = width;
  mHeight = height;
}

glm::vec3 Trackball::projectOntoHemisphere(int x, int y) {
  glm::vec3 v(0.0f);

  v.x = (2.0f * x) / mWidth - 1.0f;
  v.y = 1.0f - (2.0f * y) / mHeight;
  
  float d = sqrt(v[0] * v[0] + v[1] * v[1]);
  d = d < 1.0f ? d : 1.0f;
  v.z = sqrt(1.0f - d * d);
  
  return glm::normalize(v);
}

void Trackball::start(int x, int y) {
  mPrevPos = projectOntoHemisphere(x, y);
}

void Trackball::stop(int x, int y) {
  mCurrPos = projectOntoHemisphere(x, y);
  
  float dx, dy, dz, length;
  dx = mCurrPos.x - mPrevPos.x;
  dy = mCurrPos.y - mPrevPos.y;
  dz = mCurrPos.z - mPrevPos.z;
  length = sqrt(dx * dx + dy * dy + dz * dz);

  if (length > 0) {
    mAxis = glm::cross(mPrevPos, mCurrPos);
    mAngle = glm::angle(mPrevPos, mCurrPos);
    mRotationMatrix = glm::rotate(mAngle * 0.1f, mAxis);

    glm::vec3 forward = mCamera->mRef - mCamera->mEye;
    glm::vec3 rotatedForward = glm::vec3(glm::inverse(mRotationMatrix) * glm::vec4(forward, 0.0f));
    mCamera->mEye = mCamera->mRef - rotatedForward;
    mCamera->mUp = glm::vec3(glm::inverse(mRotationMatrix) * glm::vec4(mCamera->mUp, 0.0f));
  }
}
