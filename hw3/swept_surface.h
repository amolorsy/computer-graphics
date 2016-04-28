#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

const int B_SPLINE = 0;
const int CATMULL_ROM_SPLINE = 1;

static inline float b_spline_polynomial(float *U, float *G) {
  return ((-1.0f * U[0] + 3.0f * U[1] - 3.0f * U[2] + 1.0f) * G[0]
    + (3.0f * U[0] - 6.0f * U[1] + 0.0f + 4.0f) * G[1]
    + (-3.0f * U[0] + 3.0f * U[1] + 3.0f * U[2] + 1.0f) * G[2]
    + (1.0f * U[0] + 0.0f + 0.0f + 0.0f) * G[3]) / 6.0f;
}

static inline float catmull_rom_spline_polynomial(float *U, float *G) {
  return ((-1.0f * U[0] + 2.0f * U[1] - 1.0f * U[2] + 0.0f) * G[0]
    + (3.0f * U[0] - 5.0f * U[1] + 0.0f + 2.0f) * G[1]
    + (-3.0f * U[0] + 4.0f * U[1] + 1.0f * U[2] + 0.0f) * G[2]
    + (1.0f * U[0] - 1.0f * U[1] + 0.0f + 0.0f) * G[3]) / 2.0f;
}
