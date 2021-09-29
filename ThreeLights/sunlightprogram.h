#ifndef SUNLIGHTPROGRAM_H
#define SUNLIGHTPROGRAM_H

#include <GL/glew.h>

#include "lightprogram.h"
#include "light.h"


class SunLightProgram : public LightProgram{
public:
    void SetLight(const SunLight & light) const;
    void Initialize(const char *vertex_shader_file, const char *fragment_shader_file);
private:
    struct {
        GLuint ambient;
        GLuint diffuse;
        GLuint position;
        GLuint specular;
    }light_locations_;
};

#endif // SUNLIGHTPROGRAM_H
