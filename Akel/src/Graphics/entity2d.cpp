// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/03/2022
// Updated : 18/09/2022

#include <Graphics/entity.h>
#include <Core/core.h>

#define R_MASK 0xFF000000
#define G_MASK 0x00FF0000
#define B_MASK 0x0000FF00
#define A_MASK 0x000000FF

namespace Ak
{
	Entity2D::Entity2D(Models _model, Maths::Vec2<float> _position, Maths::Vec2<float> _scale, Maths::Vec4<float> _color)
	{
	    model = _model;
		position = std::move(_position);
		scale = std::move(_scale);
		color = std::move(_color);
	}

	Entity2D::Entity2D(Models _model, Maths::Vec2<float> _position, Maths::Vec2<float> _scale, Colors _color)
    {
	    model = _model;
		position = std::move(_position);
		scale = std::move(_scale);
        uint32_t col_val = static_cast<uint32_t>(_color);
        color.SET(static_cast<float>((col_val & R_MASK) >> 24) / 255, static_cast<float>((col_val & G_MASK) >> 16) / 255, static_cast<float>((col_val & B_MASK) >> 8) / 255, static_cast<float>((col_val & A_MASK)) / 255);
    }

	void Entity2D::initBuffers()
	{
        switch(model)
        {
            case Models::quad :
			{
				std::vector<Vertex2D> vertexData;
                vertexData = {
                    {position, color},
                    {{position.X + scale.X, position.Y}, color},
                    {{position.X + scale.X, position.Y + scale.Y}, color},
                    {{position.X, position.Y + scale.Y}, color}
                };

				std::vector<uint32_t> indexData;
                indexData = { 0, 1, 2, 2, 3, 0 };

				_vbo.create(sizeof(Vertex2D) * vertexData.size(), vertexData.data());
				_ibo.create(sizeof(uint32_t) * indexData.size(), indexData.data());

				break;
			}

            case Models::triangle :
            break;

            case Models::cube : Core::log::report(FATAL_ERROR, "Entity 2D : a cube cannot be a 2D entity, you may use the \"quad\" model"); break;

            default : Core::log::report(ERROR, "Entity 2D : bad model"); break;
        }
	}
}
