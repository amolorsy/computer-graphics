#include "control_point.h"

ControlPoint::ControlPoint(float x, float z) {
  mX = x;
  mZ = z;
}

ControlPoint::~ControlPoint() {
}

float ControlPoint::getX() {
  return mX;
}

float ControlPoint::getZ() {
  return mZ;
}
