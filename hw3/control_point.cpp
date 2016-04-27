#include "control_point.h"

ControlPoint::ControlPoint(float x, float y) {
  mX = x;
  mY = y;
}

ControlPoint::~ControlPoint() {
}

float ControlPoint::getX() {
  return mX;
}

float ControlPoint::getY() {
  return mY;
}
