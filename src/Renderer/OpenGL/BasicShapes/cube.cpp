// This file is a part of AtlasEngine
// CREATED : 30/04/2021
// UPDATED : 05/05/2021

#include <Utils/utils.h>

namespace AE::GL
{
	Cube::Cube() : _vbo(GL_ARRAY_BUFFER), _ibo(GL_ELEMENT_ARRAY_BUFFER)
	{
		_vbo.generate();
		_ibo.generate();

		//    v6------v5
		//   /|      /|
		//  v1------v0|
		//  | |     | |
		//  | v7----|-v4
		//  |/      |/
		//  v2------v3

		// vertex position array
		std::array<float, 72> const vertices {
			 1.0, 1.0, 1.0,  -1.0, 1.0, 1.0,  -1.0,-1.0, 1.0,  1.0,-1.0, 1.0, // top
			 1.0, 1.0, 1.0,   1.0,-1.0, 1.0,   1.0,-1.0,-1.0,  1.0, 1.0,-1.0, // back
			 1.0, 1.0, 1.0,   1.0, 1.0,-1.0,  -1.0, 1.0,-1.0, -1.0, 1.0, 1.0, // left
			-1.0, 1.0, 1.0,  -1.0, 1.0,-1.0,  -1.0,-1.0,-1.0, -1.0,-1.0, 1.0, // front
			-1.0,-1.0,-1.0,   1.0,-1.0,-1.0,   1.0,-1.0, 1.0, -1.0,-1.0, 1.0, // right
			 1.0,-1.0,-1.0,  -1.0,-1.0,-1.0,  -1.0, 1.0,-1.0,  1.0, 1.0,-1.0  // bottom
		};

		// normal array
		std::array<float, 72> const normales {
				 0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,  // top
				 1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0,  // back
				 0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,  // left
				-1, 0, 0,  -1, 0, 0,  -1, 0, 0,  -1, 0, 0,  // front
				 0,-1, 0,   0,-1, 0,   0,-1, 0,   0,-1, 0,  // right
				 0, 0,-1,   0, 0,-1,   0, 0,-1,   0, 0,-1   // bottom
		};

		std::array<float, 96> const couleurs {
				 0, 1, 0, 1,   0, 1, 0, 1,   0, 1, 0, 1,   0, 1, 0, 1,  // top
				 1, 0, 1, 1,   1, 0, 1, 1,   1, 0, 1, 1,   1, 0, 1, 1,  // back
				 0, 0, 1, 1,   0, 0, 1, 1,   0, 0, 1, 1,   0, 0, 1, 1,  // left
				 1, 0, 0, 1,   1, 0, 0, 1,   1, 0, 0, 1,   1, 0, 0, 1,  // front
				 1, 1, 0, 1,   1, 1, 0, 1,   1, 1, 0, 1,   1, 1, 0, 1,  // right
				 0, 1, 1, 1,   0, 1, 1, 1,   0, 1, 1, 1,   0, 1, 1, 1   // bottom
		};

		// index array for glDrawElements()
		// A cube requires 36 indices = 6 sides * 2 tris * 3 verts
		std::array<unsigned int, 36> indices {
			 0,  1,  2,   2,  3,  0,    // top
			 4,  5,  6,   6,  7,  4,    // back
			 8,  9, 10,  10, 11,  8,    // left
			12, 13, 14,  14, 15, 12,    // front
			16, 17, 18,  18, 19, 16,    // right
			20, 21, 22,  22, 23, 20     // bottom
		};

		for(int i = 0; i < sizeof(indices); i++)
		{
			_indices.push_back(indices[i]);
		}

		for(int i = 0; i < sizeof(vertices); i++)
		{
			_vertices.push_back(vertices[i]);
			_normales.push_back(normales[i]);
		}
		for(int i = 0; i < sizeof(couleurs); i++)
		{
			_couleurs.push_back(couleurs[i]);
		}

		_nOffset = _vertices.size();
		_cOffset = _nOffset + _normales.size();
/*
		_vbo.bindBuffer();
		_vbo.setSize(_vertices.size() + _normales.size() + _couleurs.size());
		_vbo.pushData(0, _vertices);
		_vbo.pushData(_vertices.size(), _normales);
		_vbo.pushData(_vertices.size() + _normales.size(), _couleurs);
		_vbo.unbindBuffer();

		_ibo.bindBuffer();
		_ibo.setSize(_indices.size());
		_ibo.pushData(0, _indices);
		_ibo.unbindBuffer();
*/
		if(glIsBuffer(_vboID) == GL_TRUE) glDeleteBuffers(1, &_vboID);
		if(glIsBuffer(_iboID) == GL_TRUE) glDeleteBuffers(1, &_iboID);

		// Génération de l'ID
		glGenBuffers(1, &_vboID);

		// Verrouillage du VBO
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		// Allocation de la mémoire vidéo
		glBufferData(GL_ARRAY_BUFFER, _vertices.size() + _normales.size() + _couleurs.size(), 0, GL_STATIC_DRAW);
		// Transfert des données
		glBufferSubData(GL_ARRAY_BUFFER, 0, _vertices.size(), &_vertices[0]);                                                                   // copy verts at offset 0
		glBufferSubData(GL_ARRAY_BUFFER, _vertices.size(), _normales.size(), &_normales[0]);                                                   // copy norms after verts
		glBufferSubData(GL_ARRAY_BUFFER, _vertices.size() + _normales.size(), _couleurs.size(), &_couleurs[0]);                               // copy cols after norms
		// Déverrouillage du VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &_iboID);
		// Verouillage de l'IBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboID);
		// Allocation de la mémoire vidéo
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size(), &_indices[0], GL_STATIC_DRAW);
		// Dévérouillage de l'IBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		if(glIsBuffer(_vboID) != GL_TRUE || glIsBuffer(_iboID) != GL_TRUE)
			messageBox(ERROR, "nope dude", std::string(reinterpret_cast<const char*>(glewGetErrorString(glIsBuffer(_iboID)))));
	}

	void Cube::setColor(int red, int green, int blue)
	{}

	void Cube::setPosition(int x, int y, int z)
	{
		_pos_x = x;
		_pos_y = y;
		_pos_z = z;
	}

	void Cube::setSize(int size)
	{}

	void Cube::render(Shader& shader)
	{
		glEnable(GL_DEPTH_TEST);

		Matrixes::MatrixMode(AE_MODEL_MATRIX);
		Matrixes::LoadIdentity();
		Matrixes::Translate3D(_pos_x, _pos_y, _pos_z);
        shader.setMat4("model", Matrixes::getMatrix(AE_MODEL_MATRIX));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);  // Enable shader's attributes
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);

        //_vbo.bindBuffer();
		//_ibo.bindBuffer();
/*		
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboID);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)_cOffset); // Passing info to shader
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void*)_nOffset);

        // finally draw a cube with glDrawRangeElements()
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);

        //_vbo.unbindBuffer();
        //_ibo.unbindBuffer();
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
*/
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, &_vertices[0]);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, &_couleurs[0]);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, &_normales[0]);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, &_indices[0]);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);	// Disable shader's attributes
		glDisableVertexAttribArray(3);
	}

	Cube::~Cube()
	{
		_vbo.deleteBuffer();
		_ibo.deleteBuffer();

		glDeleteBuffers(1, &_vboID);
		glDeleteBuffers(1, &_iboID);

	}
}

