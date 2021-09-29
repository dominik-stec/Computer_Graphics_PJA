#ifndef MATMA_H
#define MATMA_H

#ifndef M_PI
    #define M_PI 3.14159265
#endif

class Mat4{
public:
    Mat4(); // Unit matrix
    operator const float* () const{return matrix_;}
    static Mat4 CreateProjectionMatrix(float fovy,
                                       float aspect_ratio,
                                       float near_plane,
                                       float far_plane);
    void RotateAboutX(float angle); //gedrees
    void RotateAboutY(float angle); //gedrees
    void RotateAboutZ(float angle); //gedrees
    void Scale(float x_scale, float y_scale, float z_scale);
    void Translate(float delta_x, float delta_y, float delta_z);
    void SetUnitMatrix();
    void Log();
private:
    float matrix_[16]; // column-major
    void MultiplyBy(const Mat4 &);
    explicit Mat4(float);
};


#endif // MATMA_H
