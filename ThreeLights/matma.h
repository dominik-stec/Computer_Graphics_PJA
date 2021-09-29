#ifndef MATMA_H
#define MATMA_H

#include <GL/glew.h>

#ifndef M_PI
    #define M_PI 3.14159265
#endif

class Mat4{
public:
    Mat4(); // Unit matrix
    operator const float* () const{return matrix_;}
    static Mat4 CreateProjectionMatrix(GLfloat fovy,
                                       GLfloat aspect_ratio,
                                       GLfloat near_plane,
                                       GLfloat far_plane);
    void RotateAboutX(GLfloat angle); //gedrees
    void RotateAboutY(GLfloat angle); //gedrees
    void RotateAboutZ(GLfloat angle); //gedrees
    void Scale(GLfloat x_scale, GLfloat y_scale, GLfloat z_scale);
    void Translate(GLfloat delta_x, GLfloat delta_y, GLfloat delta_z);
    void SetUnitMatrix();
    void Log();
private:
    GLfloat matrix_[16]; // column-major
    void MultiplyBy(const Mat4 &);
    explicit Mat4(float);
};

class Mat3{
public:
    Mat3(); // Unit matrix
    operator const float* () const{return matrix_;}
    void RotateAboutX(GLfloat angle); //gedrees
    void RotateAboutY(GLfloat angle); //gedrees
    void RotateAboutZ(GLfloat angle); //gedrees
    void Scale(GLfloat x_scale, GLfloat y_scale, GLfloat z_scale);
    void SetUnitMatrix();
    void Log();
private:
    GLfloat matrix_[9]; // column-major
    void MultiplyBy(const Mat3 &);
    explicit Mat3(float);
};


#endif // MATMA_H
