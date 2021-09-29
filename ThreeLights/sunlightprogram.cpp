#include "sunlightprogram.h"

void SunLightProgram::Initialize(
        const char *vertex_shader_file,
        const char *fragment_shader_file){
    LightProgram::Initialize(vertex_shader_file, fragment_shader_file);
    light_locations_.ambient = GetUniformLocationOrDie("light.ambient");
    light_locations_.diffuse = GetUniformLocationOrDie("light.diffuse");
    light_locations_.position = GetUniformLocationOrDie("light.position");
    light_locations_.specular = GetUniformLocationOrDie("light.specular");
}


void SunLightProgram::SetLight(const SunLight & light) const{
    glUniform4fv(light_locations_.ambient, 1, light.ambient);
    glUniform4fv(light_locations_.diffuse, 1, light.diffuse);
    glUniform4fv(light_locations_.specular, 1, light.specular);
    glUniform4fv(light_locations_.position, 1, light.position);
}

