#include "cross_section.h"

CrossSection::CrossSection() {
}

CrossSection::~CrossSection() {
}

void CrossSection::addControlPoint(ControlPoint controlPoint) {
  mControlPoints.push_back(controlPoint);
}

void CrossSection::setScalingFactor(float scalingFactor) {
  mScalingFactor = scalingFactor;
}

void CrossSection::setRotationFactor(std::vector<float> rotationFactor) {
  mRotationFactor = rotationFactor;
}

void CrossSection::setTranslationFactor(std::vector<float> translationFactor) {
  mTranslationFactor = translationFactor;
}

std::vector<ControlPoint> CrossSection::getControlPoints() {
  return mControlPoints;
}

float CrossSection::getScalingFactor() {
  return mScalingFactor;
}

std::vector<float> CrossSection::getRotationFactor() {
  return mRotationFactor;
}

std::vector<float> CrossSection::getTranslationFactor() {
  return mTranslationFactor;
}
