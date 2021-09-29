#include "lightprogram.h"

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;


void LightProgram::Initialize(const char *vertex_shader_file, const char *fragment_shader_file){
    TextureCameraProgram::Initialize(vertex_shader_file, fragment_shader_file);
    normal_matrix_location_ = GetUniformLocationOrDie("normal_matrix");
    material_locations_.emission = GetUniformLocationOrDie("material.emission");
    material_locations_.ambient = GetUniformLocationOrDie("material.ambient");
    material_locations_.diffuse = GetUniformLocationOrDie("material.diffuse");
    material_locations_.specular = GetUniformLocationOrDie("material.specular");
    material_locations_.shininess = GetUniformLocationOrDie("material.shininess");

//    glUseProgram(0); //(moved to Window::InitPrograms())
}

void LightProgram::SetMaterial(const Material & material) const{
    glUniform4fv(material_locations_.ambient, 1, material.ambient);
    glUniform4fv(material_locations_.emission, 1, material.emission);
    glUniform4fv(material_locations_.diffuse, 1, material.diffuse);
    glUniform4fv(material_locations_.specular, 1, material.specular);
    glUniform1f(material_locations_.shininess, material.shininess);
}

void LightProgram::SetNormalMatrix(const Mat3 & matrix) const{
    glUniformMatrix3fv(normal_matrix_location_, 1, GL_TRUE, matrix);
}

