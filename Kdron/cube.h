#ifndef CUBE_H
#define CUBE_H

#include <GL/glew.h>

#include "indexmodel.h"
#include "movablemodel.h"
#include "modelprogram.h"
#include "matma.h"

class Cube: public IndexModel, public MovableModel{
 public:
    Cube(float init_velocity=10, float init_angle=0);
    void SetInitAngle(float angle){angle_= angle;}
    void SetVelocity(float velocity){velocity_= velocity;}
    void Initialize();
    void Draw(const ModelProgram & program) const;
    void Move(float delta_t);
    void SpeedUp();
    void SlowDown();
    void ToggleAnimated();
 private:
    float angle_;
    float velocity_;
    bool animated_;
};

#endif // CUBE_H
