#ifndef TEXTURECAMERAPROGRAM_H
#define TEXTURECAMERAPROGRAM_H

#include <GL/glew.h>

#include "matma.h"
#include "modelprogram.h"

class TextureCameraProgram: public ModelProgram{
public:
    void Initialize(const char* vertex_shader_file,
                    const char* fragment_shader_file);
    void SetTextureUnit(GLuint) const;
private:
    GLuint texture_unit_location_;
};

#endif // TEXTURECAMERAPROGRAM_H
