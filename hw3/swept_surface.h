#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include "glm-0.9.7.4/glm/glm.hpp"
#include "glm-0.9.7.4/glm/gtc/type_ptr.hpp"
#include "glm-0.9.7.4/glm/gtc/matrix_transform.hpp"
#include "glm-0.9.7.4/glm/gtx/rotate_vector.hpp"
#include "glm-0.9.7.4/glm/gtc/matrix_inverse.hpp"
#include "glm-0.9.7.4/glm/gtx/vector_angle.hpp"
#include "glm-0.9.7.4/glm/gtx/transform.hpp"

#include "mesh.h"
#include "data.h"
#include "trackball.h"

const int B_SPLINE = 0;
const int CATMULL_ROM_SPLINE = 1;

const int STEPS = 5;

/* For light and material */
const GLfloat AMBIENT_LIGHT[] = { 0.1f, 0.1f, 0.0f, 1.0f };
const GLfloat DIFFUSE_LIGHT[] = { 1.0f, 1.0f, 0.0f, 1.0f };
const GLfloat SPECULAR_LIGHT[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat LIGHT_POSITION[] = { -100.0f, 125.0f, 100.0f, 1.0f };

const GLfloat AMBIENT_SUB_LIGHT[] = { 0.3f, 0.3f, 0.3f, 1.0f };
const GLfloat DIFFUSE_SUB_LIGHT[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat SUB_LIGHT_POSITION[] = { 7.0f, 0.0f, -5.0f, 1.0f };

const GLfloat MATERIAL_AMBIENT[] = { 0.0f, 0.75f, 0.0f, 1.0f };
const GLfloat MATERIAL_SPECULAR[] = { 1.0f, 1.0f, 1.0f, 1.0f };
/* End */

static inline int circularIndex(int size, int index) {
  return index < 0 ? size - 1 + index : (index >= size ? index - size : index);
}

static inline float bSplinePolynomial(float *U, float *G) {
  return ((-1.0f * U[0] + 3.0f * U[1] - 3.0f * U[2] + 1.0f) * G[0]
    + (3.0f * U[0] - 6.0f * U[1] + 0.0f + 4.0f) * G[1]
    + (-3.0f * U[0] + 3.0f * U[1] + 3.0f * U[2] + 1.0f) * G[2]
    + (1.0f * U[0] + 0.0f + 0.0f + 0.0f) * G[3]) / 6.0f;
}

static inline float catmullRomSplinePolynomial(float *U, float *G) {
  return ((-1.0f * U[0] + 2.0f * U[1] - 1.0f * U[2] + 0.0f) * G[0]
    + (3.0f * U[0] - 5.0f * U[1] + 0.0f + 2.0f) * G[1]
    + (-3.0f * U[0] + 4.0f * U[1] + 1.0f * U[2] + 0.0f) * G[2]
    + (1.0f * U[0] - 1.0f * U[1] + 0.0f + 0.0f) * G[3]) / 2.0f;
}
