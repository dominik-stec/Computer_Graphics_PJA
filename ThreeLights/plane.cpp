#include "plane.h"

#include <GL/glew.h>

void Plane::Initialize(int m, int n){
    m_=m;
    n_=n;
    int i, j, pos;

    //model_matrix_.Translate(0, -3, 0);
    //stare
    model_matrix_.Translate(0, -8, 0);//oddala tlo
	model_matrix_.RotateAboutX(90);//ustawia plane jako pionowe tlo
	model_matrix_.Scale(6, 12, 2);//powieksza tlo
	
    NormalTextureVertex* vertices = new NormalTextureVertex[(m_ + m_ + 1)*(n_ + n_ +1)];

    for (i=n_; i>= -n_; i--) {
      for (j=-m_; j<=m_; j++){
        int pos=(n_-i)*(m_+m_+1)+j+m_;
        vertices[pos].position[0]=j;
        vertices[pos].position[1]=0.0f;
        vertices[pos].position[2]=i;
        vertices[pos].position[3]=1.0f;
        vertices[pos].texture[0]=(float)j/(float)m_;
        vertices[pos].texture[1]=(float)i/(float)n_;
        vertices[pos].normal[0]=0.0f;
        vertices[pos].normal[1]=1.0f;
        vertices[pos].normal[2]=0.0f;
      }
    }

    GLuint* indices = new GLuint[4*n_*(2*m_+1)];

    int k=0;

    for(i=0; i<2*n_; i++){
      for(j=0; j<(2*m_+1); j++){
        pos=2*(i*(2*m_+1)+j);
        indices[pos]=k;
        indices[pos+1]=k+(2*m_+1);
        k++;
      }
    }

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glGenBuffers(1, &vertex_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glBufferData(GL_ARRAY_BUFFER,
            (m_+m_+1)*(n_+n_+1)*sizeof(vertices[0]),
            vertices,
            GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]),
            (GLvoid*)sizeof(vertices[0].position));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]),
            (GLvoid*)(sizeof(vertices[0].position)+sizeof(vertices[0].texture)));
    glEnableVertexAttribArray(3);

    glGenBuffers(1, &index_buffer_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 4*n_*(2*m_+1)*sizeof(GLuint),
                 indices,
                 GL_STATIC_DRAW
                 );
    delete [] vertices;
    delete [] indices;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}



void Plane::Draw(const LightProgram & program) const{

    glBindVertexArray(vao_);


    glUseProgram(program);
    program.SetModelMatrix(model_matrix_);
    program.SetNormalMatrix(normal_matrix_);
    program.SetMaterial(material_);


    glActiveTexture(texture_unit_);
    glBindTexture(GL_TEXTURE_2D, texture_);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    for (int i=0;i<2*n_;i++){
      glDrawElements(GL_TRIANGLE_STRIP, 2*(2*n_+1),
                     GL_UNSIGNED_INT,
                     (GLvoid*)(sizeof(GLuint) * 2*i*(2*m_+1)));
    }

    glDisable(GL_CULL_FACE);

    glBindVertexArray(0);
    glUseProgram(0);
}
