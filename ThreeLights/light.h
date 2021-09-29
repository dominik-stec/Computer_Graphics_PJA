#ifndef LIGHT
#define LIGHT
#include <GL/glew.h>

typedef struct PointLight{
  GLfloat position[4];
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat attenuation[3];
} PointLight;


typedef struct SpotLight{
  GLfloat position[4];
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat attenuation[3];
  GLfloat direction[3];
  GLfloat cutoff;
  GLfloat exponent;
} SpotLight;

typedef struct SunLight{
  GLfloat position[4];
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
} SunlLight;



#endif // LIGHT

