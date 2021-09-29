#ifndef MATERIAL
#define MATERIAL
#include <GL/glew.h>

typedef struct Material{
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat emission[4];
  GLfloat shininess;
} Material;


#endif // MATERIAL

