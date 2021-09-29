#include "twospheres.h"
#include "vertices.h"

#include <iostream>
#include <cmath>

TwoSpheres::TwoSpheres(float init_velocity, float init_angle){
    velocity_ = init_velocity;
    angle_ = init_angle;
    animated_ = true;
}


void TwoSpheres::Move(float delta_t){
    if (!animated_) return;
    angle_ += delta_t * velocity_;
    if(angle_>360) angle_ -= 360;
    if(angle_<-360) angle_ += 360;
    model_matrix_.SetUnitMatrix();
    //nie obraca sie wokol X
	//model_matrix_.RotateAboutX(angle_);
	//model_matrix_.RotateAboutZ(-23);
    model_matrix_.RotateAboutY(angle_); //obrot ziemi wokol wlasnej osi
	model_matrix_.RotateAboutZ(-23); //ustawia rzeczywiste nachylenie osi obrotu ziemi

}



void TwoSpheres::SpeedUp(){
    velocity_ *= 1.09544511501;
}

void TwoSpheres::SlowDown(){
    velocity_ /= 1.09544511501;
}

void TwoSpheres::ToggleAnimated(){
    animated_ = ! animated_;
}

void TwoSpheres::Initialize(int n, int m, float R, float r){
    n_=n;
    m_=m;

	//model_matrix_.Scale(-10, -10, -10);//zmniejsza teksture
	//model_matrix_.Translate(4, 4, 4);//przesuwa teksture na sferze

    TextureVertex * vertices=new TextureVertex[(m_ + 1)*(n_ + 1)];
    int i,j;
    for (i=0;i<=n_;i++) {
      float phi=2*M_PI/(float)n_*i;
      for (j=0;j<=m_;j++){
        float theta=2*M_PI/(float)m_*j;
        //zamiana torusa na sfere
		vertices[i*(m_ + 1)+j].position[0]=R*sin(theta)*cos(phi);
        vertices[i*(m_ + 1)+j].position[1]=R*sin(phi);
        vertices[i*(m_ + 1)+j].position[2]=R*cos(theta)*cos(phi);
        /*
        vertices[i*(m_ + 1)+j].position[0]=(R + r*cos(phi))*sin(theta);
        vertices[i*(m_ + 1)+j].position[1]=r*sin(phi);
        vertices[i*(m_ + 1)+j].position[2]=(R + r*cos(phi))*cos(theta);
         */
        vertices[i*(m_ + 1)+j].position[3]=1.0f;
        vertices[i*(m_ + 1)+j].texture[0]=(float)j/(float)m_;
        vertices[i*(m_ + 1)+j].texture[1]=(float)i/(float)n_;
      }
    }



    GLuint * indices=new GLuint[2*n_*(m_ + 1)];

    unsigned int k=0;

    for(i=0; i<=n_ - 1; i++){
      for(j=0; j<=m_; j++){
        indices[2*(i*(m_ + 1)+j)]=k;
        indices[2*(i*(m_ + 1)+j)+1]=k+m_+1;
        k++;
      }
    }

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);


    glGenBuffers(1, &vertex_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glBufferData(GL_ARRAY_BUFFER,
            (m_+1)*(n_+1)*sizeof(vertices[0]),
            vertices,
            GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*)sizeof(vertices[0].position));
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &index_buffer_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 (m_+1)*n_*2*sizeof(GLuint),
                 indices,
                 GL_STATIC_DRAW
                 );
    delete [] vertices;
    delete [] indices;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void TwoSpheres::Draw(const TextureCameraProgram &program) const{

    glBindVertexArray(vao_);
    glUseProgram(program);

    program.SetModelMatrix(model_matrix_);

    glActiveTexture(texture_unit_);
    //tekstura
    glBindTexture(GL_TEXTURE_2D, texture_);
	//dodac teltury w tej kolicy

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
    for (int i=0;i<n_;i++){
      glDrawElements(GL_TRIANGLE_STRIP,
                     2*(m_ + 1),
                     GL_UNSIGNED_INT,
                     (GLvoid*)(sizeof(GLuint) * 2 * i * (m_ + 1))
                     );
    }
    glDisable(GL_CULL_FACE);

    glBindVertexArray(0);
    glUseProgram(0);


}
