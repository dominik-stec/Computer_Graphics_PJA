#ifndef STAR_H
#define STAR_H

#include <GL/glew.h>

#include "program.h"

class Star{
 public:
    void Initialize();
    ~Star();
    void Draw(const Program & program);
 private:
    GLuint vao_;
    GLuint vertex_buffer_;
    GLuint color_buffer_;
};

#endif // TRIANGLE_H
