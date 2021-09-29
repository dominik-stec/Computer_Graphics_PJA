#ifndef PROGRAM_H
#define PROGRAM_H

#include <GL/glew.h>

class Program{
public:
    void Initialize();
    operator GLuint() const {return program_;} // to be used in glUseFunction()
    ~Program();
private:
    GLuint program_;
    GLuint vertex_shader_;
    GLuint fragment_shader_;
    GLuint CompileShaderOrDie(const char* source, GLenum type);
    GLuint LinkProgramOrDie(GLint vertex_shader, GLint fragment_shader);
};

#endif // PROGRAM_H
