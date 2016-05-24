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

#include "bsp_tree.h"
#include "material.h"
#include "trackball.h"

using namespace std;

const GLfloat AMBIENT_LIGHT[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat DIFFUSE_LIGHT[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat SPECULAR_LIGHT[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat LIGHT_POSITION[] = { 0.0f, 100.0f, 100.0f, 1.0f };

const GLfloat AMBIENT_SUB_LIGHT[] = { 0.3f, 0.3f, 0.3f, 1.0f };
const GLfloat DIFFUSE_SUB_LIGHT[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat SPECULAR_SUB_LIGHT[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat SUB_LIGHT_POSITION[] = { 0.0f, 1000.0f, 0.0f, 1.0f };
