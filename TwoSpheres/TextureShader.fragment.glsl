#version 430

in vec2 tex_coord;

out vec4 out_color;

uniform sampler2D texture_unit;

void main(void){
    out_color = texture(texture_unit, tex_coord);
}
