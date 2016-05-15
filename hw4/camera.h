#include <vector>
#include <cmath>

#include <GL/gl.h>
#include <GL/glu.h>

#include "glm-0.9.7.4/glm/glm.hpp"
#include "glm-0.9.7.4/glm/gtc/type_ptr.hpp"
#include "glm-0.9.7.4/glm/gtc/matrix_transform.hpp"
#include "glm-0.9.7.4/glm/gtx/rotate_vector.hpp"
#include "glm-0.9.7.4/glm/gtc/matrix_inverse.hpp"

const int DIRECTION_UP = 0;
const int DIRECTION_DOWN = 1;
const int DIRECTION_LEFT = 2;
const int DIRECTION_RIGHT = 3;

class Camera {
  private:
    float mFovY;
    float mAspect;
    float mNear;
    float mFar;

    glm::mat4 mProjectionMatrix;
    glm::mat4 mViewMatrix;

  public:
    glm::vec3 mEye;
    glm::vec3 mRef;
    glm::vec3 mUp;
    
    Camera(int width, int height);
    ~Camera();

    void dollyIn();
    void dollyOut();
    void zoomIn();
    void zoomOut();
    void pan(int direction);
    void showAll(std::vector<glm::vec3> vertices);
    void seek(int x, int y);

    void changeAspect(float aspect);
    glm::mat4 calculateProjectionMatrix();
    glm::mat4 calculateViewMatrix();
};
