#ifndef PROGRAM_H
#define PROGRAM_H

#include <GL/glew.h>

#include "matma.h"

class Program{
public:
    void Initialize(const char* vertex_shader_file, const char* fragment_shader_file);
    operator GLuint() const{return program_;} // to be used in glUseFunction()
    void SetModelMatrix(const Mat4 &) const;
    ~Program();
    void SetViewMatrix(const Mat4 &);
    void SetProjectionMatrix(const Mat4 &);
private:
    GLuint program_;
    GLuint vertex_shader_;
    GLuint fragment_shader_;
    GLuint model_matrix_location_;
    GLuint projection_matrix_location_;
    GLuint view_matrix_location_;

    GLuint LoadAndCompileShaderOrDie(const char* source_file, GLenum type);
    GLuint LinkProgramOrDie(GLint vertex_shader, GLint fragment_shader);

    GLint GetUniformLocationOrDie(const char *);
};

#endif // PROGRAM_H
