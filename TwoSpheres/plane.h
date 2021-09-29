#ifndef PLANE_H
#define PLANE_H

#include "indexmodel.h"
#include "movablemodel.h"
#include "texturemodel.h"
#include "matma.h"
#include "texturecameraprogram.h"

class Plane : public IndexModel, public MovableModel, public TextureModel{
public:
    void Initialize(int m, int n);
    void Draw(const TextureCameraProgram & program) const;
private:
    int n_; // mesh parameter
    int m_; // mesh parameter

};

#endif // PLANE_H
