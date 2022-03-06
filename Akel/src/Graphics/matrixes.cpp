// This file is a part of Akel
// Authors : @kbz_8
// Created : 06/03/2022
// Updated : 06/03/2022

#include <Graphics/matrixes.h>

namespace Ak
{
    glm::mat4 Matrixes::get_matrix(matrix type)
    {
        switch(type)
        {
            case matrix::proj:  return _proj;
            case matrix::model: return _model;
            case matrix::view:  return _view;

            default: break;
        }
        return glm::mat4(0.0f);
    }

    glm::mat4 Matrixes::get_current_matrix()
    {
        switch(active_matrix)
        {
            case matrix::proj:  return _proj;
            case matrix::model: return _model;
            case matrix::view:  return _view;

            default: break;
        }
        return glm::mat4(0.0f);
    }

    void Matrixes::load_identity()
    {
        switch(active_matrix)
        {
            case matrix::proj:  _proj  = glm::mat4(1.0f); break;
            case matrix::model: _model = glm::mat4(1.0f); break;
            case matrix::view:  _view  = glm::mat4(1.0f); break;

            default: break;
        }
    }
}
