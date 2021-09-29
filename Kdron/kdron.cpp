#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

#include "kdron.h"
#include "vertices.h"

Kdron::Kdron(float init_velocity, float init_angle){
    velocity_ = init_velocity;
    angle_ = init_angle;
    animated_ = true;
}


void Kdron::Move(float delta_t){
    if (!animated_) return;
    angle_ += delta_t * velocity_;
    if(angle_>360) angle_ -= 360;
    if(angle_<-360) angle_ += 360;
    model_matrix_.SetUnitMatrix();
    model_matrix_.RotateAboutX(angle_);
    model_matrix_.RotateAboutY(angle_);
}



void Kdron::SpeedUp(){
    velocity_ *= 1.09544511501;
}

void Kdron::SlowDown(){
    velocity_ /= 1.09544511501;
}

void Kdron::ToggleAnimated(){
    animated_ = ! animated_;
}

void Kdron::Initialize(){
    
    const ColorVertex kVertices[12] =
    {
        { { -1.0f, -1.0f,  1.0f, 1.0f }, { 1, 1, 1, 1 } },
        { { -1.0f, 0.0f,  1.0f, 1.0f }, { 1, 0, 0.5, 1 } },
        { { -1.0f, 0.0f,  0.0f, 1.0f }, { 1, 0, 0, 1 } },
        { {  -1.0f,  0.0f,  -1.0f, 1.0f }, { 0, 1, 0, 1 } },
        { {  0.0f, 1.0f,  -1.0f, 1.0f }, { 1, 1, 0, 1 } },
        { { 1.0f, 0.0f, -1.0f, 1.0f }, { 0, 0, 1, 1 } },
        { { 1.0f,  -1.0f, -1.0f, 1.0f }, { 1, 0, 0, 1 } },
        { {  1.0f,  0.0f, 0.0f, 1.0f }, { 1, 0, 1, 1 } },
        { {  1.0f, 0.0f, 1.0f, 1.0f }, { 0, 0, 0, 1 } },        
        { {  -1.0f, -1.0f, -1.0f, 1.0f }, { 0, 0, 0, 1 } },
        { {  1.0f, -1.0f, 1.0f, 1.0f }, { 0, 0, 0, 1 } },
        { {  0.0f, -1.0f, 1.0f, 1.0f }, { 0, 0, 0, 1 } }
    };

	
    const GLuint kIndices[60] =
    {
      
      8,7,10,  10,7,6,  7,5,6,
      2,4,11,  11,4,7,  
      0,1,11, 
      11,8,10,  
      0,1,2,  0,2,3,  0,3,9,
      0,9,11,  9,6,11,  11,6,10,
      1,2,11,  
      11,8,7,
      2,4,3,
      7,4,5,
      9,3,4,  9,4,6,  6,4,5
        
    };


    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glGenBuffers(1, &vertex_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kVertices), kVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(kVertices[0]), (GLvoid*) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(kVertices[0]),
                          (GLvoid*) sizeof(kVertices[0].position));
    glEnableVertexAttribArray(1);


    glGenBuffers(1, &index_buffer_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(kIndices), kIndices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void Kdron::Draw(const ModelProgram &program) const{

    glUseProgram(program);
    glBindVertexArray(vao_);

    program.SetModelMatrix(model_matrix_);

    glDrawElements(GL_TRIANGLES, 60, GL_UNSIGNED_INT, (GLvoid*) 0);

    glBindVertexArray(0);
    glUseProgram(0);


}

void Kdron::RoundLeft(){
model_matrix_.RotateAboutY(-5);
}

void Kdron::RoundRight(){
model_matrix_.RotateAboutY(5);
}

void Kdron::RoundUp(){
model_matrix_.RotateAboutX(-5);
}

void Kdron::RoundDown(){
model_matrix_.RotateAboutX(5);
}



