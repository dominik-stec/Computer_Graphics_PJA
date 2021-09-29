#include "spotlightprogram.h"

#include "cmath"

#ifndef M_PI
    #define M_PI 3.14159265
#endif

void SpotLightProgram::Initialize(
        const char *vertex_shader_file,
        const char *fragment_shader_file){
    LightProgram::Initialize(vertex_shader_file, fragment_shader_file);
    light_locations_.ambient = GetUniformLocationOrDie("light.ambient");
    light_locations_.attenuation = GetUniformLocationOrDie("light.attenuation");
    light_locations_.diffuse = GetUniformLocationOrDie("light.diffuse");
    light_locations_.position = GetUniformLocationOrDie("light.position");
    light_locations_.specular = GetUniformLocationOrDie("light.specular");
    light_locations_.direction = GetUniformLocationOrDie("light.direction");
    light_locations_.cutoff = GetUniformLocationOrDie("light.cutoff");
    light_locations_.exponent = GetUniformLocationOrDie("light.exponent");
}


void SpotLightProgram::SetLight(const SpotLight & light) const{
    glUniform4fv(light_locations_.ambient, 1, light.ambient);
    glUniform4fv(light_locations_.diffuse, 1, light.diffuse);
    glUniform4fv(light_locations_.specular, 1, light.specular);
    glUniform4fv(light_locations_.position, 1, light.position);
    glUniform3fv(light_locations_.attenuation, 1, light.attenuation);
    glUniform3fv(light_locations_.direction, 1, light.direction);
    glUniform1f(light_locations_.cutoff, cos(M_PI*light.cutoff/180.0f));
    glUniform1f(light_locations_.exponent, light.exponent);
}
