// This file is a part of AtlasEngine
// CREATED : 14/04/2021
// UPDATED : 03/06/2021

#ifndef __AE_MATRIXES__
#define __AE_MATRIXES__

#include <AEpch.h>

enum matrix
{
    AE_PROJECTION_MATRIX,
    AE_MODEL_MATRIX,
    AE_VIEW_MATRIX
};

namespace AE::GL
{
    class Matrixes
    {
        public:
            static void perspective(float FOV, float aspect, float near, float far);
            static void ortho(float left, float right, float top, float bottom);

            static void MatrixMode(matrix type);
            static glm::mat4 getMatrix(matrix type);
            static glm::mat4 getCurrentMatrix();

            static void lookAt(float pos_x, float pos_y, float pos_z, float target_x, float target_y, float target_z, float up_x, float up_y, float up_z);

            static void LoadIdentity();

            static void Translate3D(double x, double y, double z);
            
        private:
            inline static glm::mat4 AEprojection;
            inline static glm::mat4 AEmodel;
            inline static glm::mat4 AEview;

            inline static matrix ACTIVE_MATRIX;
    };
}

#endif // __AE_MATRIXES__
