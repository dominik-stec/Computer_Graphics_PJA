#include "texturecameraprogram.h"

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;


void TextureCameraProgram::Initialize(const char *vertex_shader_file,
                                      const char *fragment_shader_file){
    ModelProgram::Initialize(vertex_shader_file, fragment_shader_file);
    texture_unit_location_ = GetUniformLocationOrDie("texture_unit");
}

void TextureCameraProgram::SetTextureUnit(GLuint t) const{
    glUniform1i(texture_unit_location_, t);
}
