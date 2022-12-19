// This file is a part of Akel
// Authors : @kbz_8
// Created : 06/03/2022
// Updated : 19/12/2022

#ifndef __AK_MATRIXES__
#define __AK_MATRIXES__

#include <Akpch.h>

namespace Ak
{
    enum class matrix { proj, model, view };

    class Matrixes
    {
        public:
            Matrixes() = delete;

            inline static void perspective(float FOV, float aspect, float near_view, float far_view)
            { _proj = glm::perspective<float>(glm::radians(FOV), aspect, near_view, far_view); }

            inline static void ortho(float left, float right, float top, float bottom) { _proj = glm::ortho<float>(left, right, top, bottom); }

            inline static void matrix_mode(matrix type) noexcept { active_matrix = type; }
            static glm::mat4 get_matrix(matrix type);
            static glm::mat4 get_current_matrix();

            inline static void lookAt(float pos_x, float pos_y, float pos_z, float target_x, float target_y, float target_z, float up_x, float up_y, float up_z)
            { _view = glm::lookAt(glm::vec3(pos_x, pos_y, pos_z), glm::vec3(target_x, target_y, target_z), glm::vec3(up_x, up_y, up_z)); }
            
            static void load_identity();

            inline static void translate3D(float x, float y, float z) { _model = glm::translate(_model, glm::vec3(x, y, z)); }
            inline static void rotate3D(float radian_angle, float x = 0, float y = 0, float z = 0) { _model = glm::rotate(_model, radian_angle, glm::vec3(x, y, z)); }
            inline static void scale3D(float x, float y, float z) { _model = glm::scale(_model, glm::vec3(x, y, z)); }

            ~Matrixes() = delete;

        private:
            inline static glm::mat4 _proj;
            inline static glm::mat4 _model;
            inline static glm::mat4 _view;

            inline static matrix active_matrix;
    };
}

#endif // __AK_MATRIXES__
