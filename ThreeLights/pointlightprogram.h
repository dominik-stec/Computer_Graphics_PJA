#ifndef POINTLIGHTPROGRAM_H
#define POINTLIGHTPROGRAM_H

#include <GL/glew.h>

#include "lightprogram.h"
#include "light.h"


class PointLightProgram : public LightProgram{
public:
    void SetLight(const PointLight & light) const;
    void Initialize(const char *vertex_shader_file, const char *fragment_shader_file);
private:
    struct LightLocations{
        GLuint ambient;
        GLuint attenuation;
        GLuint diffuse;
        GLuint position;
        GLuint specular;
    }light_locations_;
};

#endif // POINTLIGHTPROGRAM_H
