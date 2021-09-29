#ifndef CAMERAMODELPROGRAM_H
#define CAMERAMODELPROGRAM_H

#include "cameraprogram.h"


class ModelProgram : public CameraProgram{
public:
    void Initialize(const char* vertex_shader_file, const char* fragment_shader_file);
    void SetModelMatrix(const Mat4 &) const;
private:
    GLuint model_matrix_location_;
};

#endif // CAMERAMODELPROGRAM_H
