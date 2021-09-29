#ifndef STARLINES_H
#define STARLINES_H

#include <GL/glew.h>

#include "program.h"

class Starlines{
 public:
    void Initialize();
    ~Starlines();
    void Draw(const Program & program);
 private:
    GLuint vao_;
    GLuint vertex_buffer_;
    GLuint color_buffer_;
};

#endif // TRIANGLE_H
