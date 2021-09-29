#version 430 core

layout(location=0) in vec4 in_position;
layout(location=2) in vec2 in_texture;
layout(location=3) in vec3 in_normal;


uniform mat4 model_matrix;
uniform mat3 normal_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

uniform struct SpotLight{
    vec4 position;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec3 attenuation;
    vec3 direction;
    float cutoff;
    float exponent;
} light;


out struct Vertex {
    vec2  texcoord;
    vec3  normal;
    vec3  light_dir;
    vec3  view_dir;
    float dist;
} frag_vertex;


void main(void){
    vec4 vertex   = model_matrix * in_position;
    frag_vertex.light_dir = (light.position.xyz - vertex.xyz);
    frag_vertex.normal = normal_matrix * in_normal;
    vec4 camera = -view_matrix*vec4(0.0, 0.0, 0.0, 1);
    frag_vertex.view_dir = camera.xyz-vertex.xyz;
    frag_vertex.dist = distance(light.position, vertex);
    gl_Position = (projection_matrix * view_matrix) * vertex;
    frag_vertex.texcoord = in_texture;
}

