class ControlPoint {
  private:
    float mX;
    float mZ;

  public:
    ControlPoint(float x, float z);
    ~ControlPoint();

    float getX();
    float getZ();
};
