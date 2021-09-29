#include "program.h"

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;


void Program::Initialize(const char *vertex_shader_file, const char *fragment_shader_file){
    vertex_shader_ = LoadAndCompileShaderOrDie(vertex_shader_file, GL_VERTEX_SHADER);

    fragment_shader_ = LoadAndCompileShaderOrDie(fragment_shader_file, GL_FRAGMENT_SHADER);

    program_ = LinkProgramOrDie(vertex_shader_, fragment_shader_);

    glUseProgram(program_);

    projection_matrix_location_ = GetUniformLocationOrDie("projection_matrix");
    view_matrix_location_ = GetUniformLocationOrDie("view_matrix");
    model_matrix_location_ = GetUniformLocationOrDie("model_matrix");

    glUseProgram(0);
}

GLint Program::GetUniformLocationOrDie(const char* var_name){
    GLint location=-1;
    location = glGetUniformLocation(program_, var_name);
    if (location < 0){
        cerr << "ERROR: cannot find uniform location " << var_name << endl;
        exit( EXIT_FAILURE );
    }
    return location;
}

void Program::SetModelMatrix(const Mat4 & matrix) const{
    glUniformMatrix4fv(model_matrix_location_, 1, GL_FALSE, matrix);
}

void Program::SetProjectionMatrix(const Mat4 & matrix){
    glUniformMatrix4fv(projection_matrix_location_, 1, GL_FALSE, matrix);
}

void Program::SetViewMatrix(const Mat4 & matrix){
    glUniformMatrix4fv(view_matrix_location_, 1, GL_FALSE, matrix);
}

GLuint Program::LinkProgramOrDie(GLint vertex_shader, GLint fragment_shader){
    GLuint new_program = glCreateProgram();
    glAttachShader(new_program, vertex_shader);
    glAttachShader(new_program, fragment_shader);
    glLinkProgram(new_program);

    GLint  linked;
    glGetProgramiv(new_program, GL_LINK_STATUS, &linked);
    if ( !linked ) {
        cerr << "Shader program failed to link" << endl;
        GLint  log_size;
        glGetProgramiv(new_program, GL_INFO_LOG_LENGTH, &log_size);
        char* log_msg = new char[log_size];
        glGetProgramInfoLog(new_program, log_size, NULL, log_msg);
        cerr << log_msg << endl;
        delete [] log_msg;
        exit( EXIT_FAILURE );
    }

    return new_program;
}

Program::~Program(){
    glUseProgram(0);

    glDetachShader(program_, vertex_shader_);
    glDetachShader(program_, fragment_shader_);

    glDeleteShader(fragment_shader_);
    glDeleteShader(vertex_shader_);

    glDeleteProgram(program_);

}

GLuint Program::LoadAndCompileShaderOrDie(const char * source_file, GLenum type){
    int file_size;
    char * shader_code;
    GLuint shader=glCreateShader(type);
    ifstream file (source_file, ios::in|ios::ate|ios::binary);
    if (file.is_open()) {
        file_size = file.tellg();
        shader_code = new char [file_size+1];
        file.seekg (0, ios::beg);
        file.read (shader_code, file_size);
        shader_code[file_size]='\0';
        file.close();

        glShaderSource(shader, 1, (const GLchar**) &shader_code, NULL);
        glCompileShader(shader);
        delete[] shader_code;

    }
    else{ //file was not opened
        cerr<<"Could not open the file "<<source_file<<endl;
        exit( EXIT_FAILURE );
    }

    GLint  compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        switch(type){
        case GL_VERTEX_SHADER:
            cerr << "vertex ";
        break;
        case GL_FRAGMENT_SHADER:
            cerr << "fragment ";
        break;
        }
        cerr << "shader is failed to compile:" << endl;
        GLint  log_size;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
        char* log_msg = new char[log_size];
        glGetShaderInfoLog(shader, log_size, NULL, log_msg);
        cerr << log_msg << endl;
        delete [] log_msg;
        exit( EXIT_FAILURE );
    }
    return shader;
}
