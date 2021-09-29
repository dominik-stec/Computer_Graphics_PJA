#ifndef PLANE_H
#define PLANE_H

#include "materialmodel.h"
#include "lightablemodel.h"
#include "movablemodel.h"
#include "indexmodel.h"
#include "texturemodel.h"
#include "matma.h"
#include "vertices.h"
#include "lightprogram.h"

class Plane :
        public IndexModel,
        public LightableModel,
        public MovableModel,
        public TextureModel,
        public MaterialModel{
public:
    void Initialize(int m, int n);
    void Draw(const LightProgram & program) const;
private:
    int n_; // mesh parameter
    int m_; // mesh parameter

};

#endif // PLANE_H
