#version 430 core

layout(location=0) in vec4 in_position;
layout(location=2) in vec2 in_texture;


uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

out vec2 tex_coord;

void main(void){
    gl_Position = (projection_matrix * view_matrix * model_matrix) * in_position;
    tex_coord = in_texture;
}

