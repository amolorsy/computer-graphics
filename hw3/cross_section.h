#include <vector>

#include "control_point.h"

class CrossSection {
  private:
    std::vector<ControlPoint> mControlPoints;

    float mScalingFactor;
    std::vector<float> mRotationFactor;
    std::vector<float> mTranslationFactor;

  public:
    CrossSection();
    ~CrossSection();

    void addControlPoint(ControlPoint controlPoint);
    void setScalingFactor(float scalingFactor);
    void setRotationFactor(std::vector<float> rotationFactor);
    void setTranslationFactor(std::vector<float> translationFactor);

    std::vector<ControlPoint> getControlPoints();
    float getScalingFactor();
    std::vector<float> getRotationFactor();
    std::vector<float> getTranslationFactor();
};
