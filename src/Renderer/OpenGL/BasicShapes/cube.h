// This file is a part of AtlasEngine
// CREATED : 30/04/2021
// UPDATED : 30/04/2021

#ifndef __CUBE__
#define __CUBE__

#include <AEpch.h>
#include <Renderer/renderer.h>

namespace AE::GL
{
	class Cube
	{
		public:
			Cube();
		
			void setColor(int red, int green, int blue);
			void setPosition(int x, int y, int z);
			void setSize(int size);
			void render(Shader& shader);

			~Cube();

		private:
			Buffer _vbo;
			Buffer _ibo;

			int _SIZE;

			float _taille;

			std::vector<float> _vertices;
			std::vector<float> _normales;
			std::vector<float> _couleurs;
			std::vector<uint32_t> _indices;

			int _nOffset;
			int _cOffset;

			double _pos_x;
			double _pos_y;
			double _pos_z;
	};
}

#endif // __CUBE__

