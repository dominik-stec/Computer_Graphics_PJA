#include "circlelines.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <math.h>

double Circlelines::DegreeToRad(int degree) {
	const double PI = 3.141592;
	double result = (degree * PI) / 180;
	return result;
}

double Circlelines::Xverticle(int degree) {
	double result = 0;
	const double r = 0.15;
	if (degree==0 || degree==30 || degree==60 || degree==90) {
		result = r*cos(DegreeToRad(degree));
	}
	else if (degree == 120 || degree == 150 || degree == 180) {
		result = r*cos(DegreeToRad(degree));
	}
	else if (degree == 210 || degree == 240 || degree == 270) {
		result = r*cos(DegreeToRad(degree));
	}
	else if (degree == 300 || degree == 330 || degree == 360) {
		result = r*cos(DegreeToRad(degree));
	}
	return result;
}

double Circlelines::Yverticle(int degree) {
	double result = 0;
	const double r = 0.15;
	if (degree == 0 || degree == 30 || degree == 60 || degree == 90) {
		result = r*sin(DegreeToRad(degree));
	}
	else if (degree == 120 || degree == 150 || degree == 180) {
		result = r*sin(DegreeToRad(degree));
	}
	else if (degree == 210 || degree == 240 || degree == 270) {
		result = r*sin(DegreeToRad(degree));
	}
	else if (degree == 300 || degree == 330 || degree == 360) {
		result = r*sin(DegreeToRad(degree));
	}
	return result;
}

class Degree {
private:
	double mainDegree = 0;
	
public:
	Degree(double degree) {
		mainDegree = degree;
	}
	
	void set(double degree) {
		mainDegree = degree;
	}
	
	double up(double degree) {
		mainDegree += degree;
	}
	
	double up30() {
		mainDegree += 30;
		return mainDegree;
	}
	
	double get() {
		return mainDegree;
	}

	double zero() {
		set(0);
		return mainDegree;
	}

};

void Circlelines::Initialize(){
	Degree degree(0);
	
	const GLfloat kVertices[] = {
		Xverticle(degree.get()),   Yverticle(degree.get()), 0.0f, 1.0f,
		Xverticle(degree.up30()),   Yverticle(degree.get()), 0.0f, 1.0f,
		Xverticle(degree.up30()),   Yverticle(degree.get()), 0.0f, 1.0f,
		Xverticle(degree.up30()),   Yverticle(degree.get()), 0.0f, 1.0f,
		Xverticle(degree.up30()),   Yverticle(degree.get()), 0.0f, 1.0f,
		Xverticle(degree.up30()),   Yverticle(degree.get()), 0.0f, 1.0f,
		Xverticle(degree.up30()),   Yverticle(degree.get()), 0.0f, 1.0f,
		Xverticle(degree.up30()),   Yverticle(degree.get()), 0.0f, 1.0f,
		Xverticle(degree.up30()),   Yverticle(degree.get()), 0.0f, 1.0f,
		Xverticle(degree.up30()),   Yverticle(degree.get()), 0.0f, 1.0f,
		Xverticle(degree.up30()),   Yverticle(degree.get()), 0.0f, 1.0f,
		Xverticle(degree.up30()),   Yverticle(degree.get()), 0.0f, 1.0f,
		Xverticle(degree.up30()),   Yverticle(degree.get()), 0.0f, 1.0f
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
        1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
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

Circlelines::~Circlelines(){
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &color_buffer_);
    glDeleteBuffers(1, &vertex_buffer_);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vao_);
}

void Circlelines::Draw(const Program &program){

    glUseProgram(program);
    glBindVertexArray(vao_);

// liczba wierzcholkow
    glDrawArrays(GL_LINE_LOOP, 0, 12);

    glBindVertexArray(0);
    glUseProgram(0);


}
