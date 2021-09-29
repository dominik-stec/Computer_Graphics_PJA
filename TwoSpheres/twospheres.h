#ifndef TWOSPHERES_H
#define TWOSPHERES_H

#include "indexmodel.h"
#include "movablemodel.h"
#include "texturemodel.h"
#include "matma.h"
#include "texturecameraprogram.h"

class TwoSpheres: public IndexModel, public MovableModel, public TextureModel{
 public:
    TwoSpheres(float init_velocity=40, float init_angle=0);
    void SetInitAngle(float angle){angle_= angle;}
    void SetVelocity(float velocity){velocity_= velocity;}
    void Initialize(int n, int m, float R, float r);
    void Draw(const TextureCameraProgram & program) const;
    void Move(float delta_t);
    void SpeedUp();
    void SlowDown();
    void ToggleAnimated();
    //void SelectTexturePrim(GLUint t) {texture_ = t;}
 private:
    int n_; // mesh parameter
    int m_; // mesh parameter

    float R; //big radius
    float r; //small radius

    float angle_;
    float velocity_;
    bool animated_;
		
};

#endif // TWOSPHERES_H
