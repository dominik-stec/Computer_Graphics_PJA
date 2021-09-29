#ifndef GLERROR_H
#define GLERROR_H

#include <GL/glew.h>

void GLAPIENTRY OpenglCallbackFunction(GLenum source,
                                       GLenum type,
                                       GLuint id,
                                       GLenum severity,
                                       GLsizei length,
                                       const GLchar* message,
                                       void* userParam);
#endif // GLERROR_H
