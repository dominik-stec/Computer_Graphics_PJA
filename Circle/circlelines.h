#ifndef CIRCLELINES_H
#define CIRCLELINES_H

#include <GL/glew.h>

#include "program.h"

class Circlelines{
 public:
	double DegreeToRad(int degree);
	double Xverticle(int degree);
	double Yverticle(int degree);
    void Initialize();
    ~Circlelines();
    void Draw(const Program & program);
 private:
    GLuint vao_;
    GLuint vertex_buffer_;
    GLuint color_buffer_;
};

#endif // TRIANGLE_H
