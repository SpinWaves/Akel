// This file is a part of AtlasEngine
// CREATED : 14/04/2021
// UPDATED : 14/04/2021

#include <Renderer/renderer.h>


namespace AE::GL
{
    glm::mat4 AEprojection;
    glm::mat4 AEmodel;
    glm::mat4 AEview;

    matrix ACTIVE_MATRIX;


    void perspective(float FOV, float aspect, float near, float far)
    {
        AEprojection = glm::perspective<float>(glm::radians(FOV), aspect, near, far);
    }

    void ortho(float left, float right, float top, float bottom)
    {
        AEprojection = glm::ortho<float>(left, right, bottom, top);
    }

    void MatrixMode(matrix type)
    {
        ACTIVE_MATRIX = type;
    }

    glm::mat4 getMatrix(matrix type)
    {
        switch(type)
        {
            case AE_PROJECTION_MATRIX:    return AEprojection;
            case AE_MODEL_MATRIX:         return AEmodel;
            case AE_VIEW_MATRIX:          return AEview;

            default: break;
        }
    }

    glm::mat4 getCurrentMatrix()
    {
        switch(ACTIVE_MATRIX)
        {
            case AE_PROJECTION_MATRIX: return AEprojection;
            case AE_MODEL_MATRIX:      return AEmodel;
            case AE_VIEW_MATRIX:       return AEview;

            default: break;
        }
    }

    void lookAt(float pos_x, float pos_y, float pos_z, float target_x, float target_y, float target_z, float up_x, float up_y, float up_z)
    {
        AEview = glm::lookAt(glm::vec3(pos_x, pos_y, pos_z), glm::vec3(target_x, target_y, target_z), glm::vec3(up_x, up_y, up_z));
    }

    void LoadIdentity()
    {
        switch(ACTIVE_MATRIX)
        {
            case AE_PROJECTION_MATRIX: AEprojection = glm::mat4(1.0f); break;
            case AE_MODEL_MATRIX:      AEmodel = glm::mat4(1.0f);      break;
            case AE_VIEW_MATRIX:       AEview = glm::mat4(1.0f);       break;

            default: break;
        }
    }

    void Translate3D(double x, double y, double z)
    {
        AEmodel = glm::translate(AEmodel, glm::vec3(x, y, z));
    }
}
