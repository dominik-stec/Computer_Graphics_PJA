#ifndef LIGHTPROGRAM_H
#define LIGHTPROGRAM_H

#include <GL/glew.h>

#include "matma.h"
#include "material.h"
#include "texturecameraprogram.h"

class LightProgram: public TextureCameraProgram{
public:
    void Initialize(const char* vertex_shader_file, const char* fragment_shader_file);
    void SetMaterial(const Material &material) const;
    void SetNormalMatrix(const Mat3 &) const;
private:
    GLuint normal_matrix_location_;
    struct MaterialLocations{
        GLuint emission;
        GLuint ambient;
        GLuint diffuse;
        GLuint specular;
        GLuint shininess;
    } material_locations_;

};

#endif // LIGHTPROGRAM_H
