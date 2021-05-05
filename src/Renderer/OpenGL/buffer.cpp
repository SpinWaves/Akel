// This file is a part of AtlasEngine
// CREATED : 14/04/2021
// UPDATED : 05/05/2021

#include <Renderer/renderer.h>
#include <Core/core.h>
#include <Utils/utils.h>

namespace AE::GL
{
    Buffer::Buffer(GLenum type)
    {
        _type = type;
    }

	void Buffer::generate()
	{
		deleteBuffer();
		glGenBuffers(1, &_buffer);
	}

    void Buffer::bindBuffer()
    {
    	glBindBuffer(_type, _buffer);
    }

    void Buffer::unbindBuffer()
    {
        glBindBuffer(_type, 0);
    }

    void Buffer::setSize(GLsizeiptr SIZE)
    {
    	glBufferData(_type, SIZE, 0, GL_STATIC_DRAW);
    }

    void Buffer::deleteBuffer()
    {
        if(glIsBuffer(_buffer) == GL_TRUE)
            glDeleteBuffers(1, &_buffer);
    }

    Buffer::~Buffer()
    {
        deleteBuffer();
    }
}
