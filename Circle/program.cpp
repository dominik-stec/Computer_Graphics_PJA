#include "program.h"

#include <GL/glew.h>
#include <iostream>
#include <cstdlib>

void Program::Initialize(){
    const GLchar* kVertexShaderText =
    {
        "#version 430 core\n"\

        "layout(location=0) in vec4 in_position;\n"\
        "layout(location=1) in vec4 in_color;\n"\
        "out vec4 frag_color;\n"\

        "void main(void)\n"\
        "{\n"\
        "	gl_Position = in_position;\n"\
        "	frag_color = in_color;\n"\
        "}\n"
    };

    const GLchar* kFragmentShaderText =
    {
        "#version 430 core\n"\

        "layout (location = 0) out vec4 color;\n"\
        "in vec4 frag_color;\n"\

        "void main(void)\n"\
        "{\n"\
        "	color = frag_color;\n"\
        "}\n"
    };

    vertex_shader_ = CompileShaderOrDie(kVertexShaderText, GL_VERTEX_SHADER);

    fragment_shader_ = CompileShaderOrDie(kFragmentShaderText, GL_FRAGMENT_SHADER);

    program_ = LinkProgramOrDie(vertex_shader_, fragment_shader_);

    glUseProgram(program_);
//    some actions on the created program will be placed here
    glUseProgram(0);
}

GLuint Program::LinkProgramOrDie(GLint vertex_shader, GLint fragment_shader){
    GLuint new_program = glCreateProgram();
    glAttachShader(new_program, vertex_shader);
    glAttachShader(new_program, fragment_shader);
    glLinkProgram(new_program);

    GLint  linked;
    glGetProgramiv(new_program, GL_LINK_STATUS, &linked);
    if ( !linked ) {
        std::cerr << "Shader program failed to link" << std::endl;
        GLint  log_size;
        glGetProgramiv(new_program, GL_INFO_LOG_LENGTH, &log_size);
        char* log_msg = new char[log_size];
        glGetProgramInfoLog(new_program, log_size, NULL, log_msg);
        std::cerr << log_msg << std::endl;
        delete [] log_msg;
		return 1;
		//exit( EXIT_FAILURE );
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

GLuint Program::CompileShaderOrDie(const char * source, GLenum type){
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint  compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        switch(type){
        case GL_VERTEX_SHADER:
            std::cerr << "vertex ";
        break;
        case GL_FRAGMENT_SHADER:
            std::cerr << "fragment ";
        break;
        }
        std::cerr << "shader is failed to compile:" << std::endl;
        GLint  log_size;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
        char* log_msg = new char[log_size];
        glGetShaderInfoLog(shader, log_size, NULL, log_msg);
        std::cerr << log_msg << std::endl;
        delete [] log_msg;
		return 1;
		//exit( EXIT_FAILURE );
    }
    return shader;
}
