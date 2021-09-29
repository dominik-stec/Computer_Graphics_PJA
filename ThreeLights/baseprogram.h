#ifndef BASEPROGRAM_H
#define BASEPROGRAM_H

#include <GL/glew.h>

#include "matma.h"

class BaseProgram{
public:
    void Initialize(const char* vertex_shader_file, const char* fragment_shader_file);
    operator GLuint() const{return program_;} // to be used in glUseFunction()
    ~BaseProgram();
protected:
    GLuint program_;
private:
    GLuint vertex_shader_;
    GLuint fragment_shader_;

    GLuint LoadAndCompileShaderOrDie(const char* source_file, GLenum type);
    GLuint LinkProgramOrDie(GLint vertex_shader, GLint fragment_shader);

};

#endif // PROGRAM_H
