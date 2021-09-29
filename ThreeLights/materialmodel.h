#ifndef MATERIALMODEL_H
#define MATERIALMODEL_H

#include <GL/glew.h>
#include "material.h"



class MaterialModel{
public:
    void SetMaterial(const Material & material){material_=material;}
protected:
    Material material_;
};

#endif // MATERIALMODEL_H
