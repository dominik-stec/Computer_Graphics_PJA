#ifndef CAMERAPROGRAM_H
#define CAMERAPROGRAM_H

#include <GL/glew.h>

#include "baseprogram.h"
#include "matma.h"


class CameraProgram : public BaseProgram
{
public:
    void Initialize(const char* vertex_shader_file, const char* fragment_shader_file);
    void SetViewMatrix(const Mat4 &) const;
    void SetProjectionMatrix(const Mat4 &) const;
private:
    GLuint projection_matrix_location_;
    GLuint view_matrix_location_;
protected:
    GLint GetUniformLocationOrDie(const char *);
};

#endif // CAMERAPROGRAM_H
