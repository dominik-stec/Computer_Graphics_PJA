#ifndef TORI_H
#define TORI_H

#include <GL/glew.h>

#include "lightprogram.h"
#include "movablemodel.h"
#include "lightablemodel.h"
#include "materialmodel.h"
#include "texturemodel.h"
#include "indexmodel.h"
#include "matma.h"

class Tori: public IndexModel, public TextureModel, public MovableModel, public LightableModel, public MaterialModel{
 public:
    Tori(GLfloat init_velocity=10, GLfloat init_angle=0);
    void SetMaterialPrim(const Material & material){material_prim_ = material;}
    //bis
    void SetMaterialBis(const Material & material){material_bis_ = material;}
    void SetInitAngle(GLfloat angle){angle_= angle;}
    void SetVelocity(GLfloat velocity){velocity_= velocity;}
    void Initialize(int n, int m, GLfloat R, GLfloat r);
    //LightProgram & program // const TextureCameraProgram&
    void Draw(const LightProgram & program) const;
    void Move(GLfloat delta_t);
    void SpeedUp();
    void SlowDown();
    void ToggleAnimated();
 private:
    int n_; // mesh parameter
    int m_; // mesh parameter

    Mat4 model_matrix_prim_;
    Mat3 normal_matrix_prim_;
    Material material_prim_;
    
    //bis
    Mat4 model_matrix_bis_;
    Mat3 normal_matrix_bis_;
    Material material_bis_;

    GLfloat R; //big radius
    GLfloat r; //small radius

    GLfloat angle_;
    GLfloat velocity_;
    bool animated_;

};

#endif // TORI_H
