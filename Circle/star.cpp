#include "star.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

void Star::Initialize(){
    const GLfloat kVertices[] = {
         0.150f,  0.025f, 0.0f, 1.0f,
         0.179f,  0.111f, 0.0f, 1.0f,
         0.269f,  0.111f, 0.0f, 1.0f,
         0.197f,  0.165f, 0.0f, 1.0f,
         0.223f,  0.251f, 0.0f, 1.0f,
         0.150f,  0.200f, 0.0f, 1.0f,
         0.077f,  0.251f, 0.0f, 1.0f,
         0.103f,  0.165f, 0.0f, 1.0f,
         0.031f,  0.111f, 0.0f, 1.0f,
         0.121f,  0.111f, 0.0f, 1.0f,
         0.150f,  0.025f, 0.0f, 1.0f
    };

    const GLfloat kColors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f
    };


    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glGenBuffers(1, &vertex_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kVertices), kVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &color_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kColors), kColors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

Star::~Star(){
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &color_buffer_);
    glDeleteBuffers(1, &vertex_buffer_);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vao_);
}

void Star::Draw(const Program &program){

    glUseProgram(program);
    glBindVertexArray(vao_);

// liczba wierzcholkow
    glDrawArrays(GL_TRIANGLE_FAN, 1, 10);

    glBindVertexArray(0);
    glUseProgram(0);


}
