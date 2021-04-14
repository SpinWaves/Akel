// This file is a part of AtlasEngine
// CREATED : 14/04/2021
// UPDATED : 14/04/2021

#ifndef __MATRIXES__
#define __MATRIXES__

#include <AEpch.h>

enum matrix
{
    AE_PROJECTION_MATRIX,
    AE_MODEL_MATRIX,
    AE_VIEW_MATRIX
};

namespace AE::GL
{

    void perspective(float FOV, float aspect, float near, float far);
    void ortho(float left, float right, float top, float bottom);

    void MatrixMode(matrix type);
    glm::mat4 getMatrix(matrix type);
    glm::mat4 getCurrentMatrix();

    void lookAt(float pos_x, float pos_y, float pos_z, float target_x, float target_y, float target_z, float up_x, float up_y, float up_z);

    void LoadIdentity();

    void Translate3D(double x, double y, double z);
}

#endif // __MATRIXES__
