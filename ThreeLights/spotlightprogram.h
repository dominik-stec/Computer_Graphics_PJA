#ifndef SPOTLIGHTPROGRAM_H
#define SPOTLIGHTPROGRAM_H

#include "lightprogram.h"
#include "light.h"

class SpotLightProgram : public LightProgram{
public:
    void SetLight(const SpotLight & light) const;
    void Initialize(const char *vertex_shader_file, const char *fragment_shader_file);
private:
    struct {
        GLuint ambient;
        GLuint attenuation;
        GLuint diffuse;
        GLuint position;
        GLuint specular;
        GLuint direction;
        GLuint cutoff;
        GLuint exponent;
    }light_locations_;
};

#endif // SPOTLIGHTPROGRAM_H
