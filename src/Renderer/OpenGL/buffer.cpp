// This file is a part of AtlasEngine
// CREATED : 14/04/2021
// UPDATED : 30/04/2021

#include <Renderer/renderer.h>
#include <Platform/platform.h>
#include <Core/core.h>

namespace AE::GL
{
    Buffer::Buffer(GLenum type)
    {
        _type = type;
        _buffer = 0;
    }

    void Buffer::generate()
    {
        deleteBuffer();
        glGenBuffers(1, &_buffer);
        if(glIsBuffer(_buffer) != GL_TRUE)
		{
			GLenum err;
            messageBox(ERROR, "Unable to generate a Buffer", AE_CATCH_GL_BUFFER_GENERATION);
    	}
	}

    void Buffer::bindBuffer()
    {
        if(glIsBuffer(_buffer) == GL_TRUE)
            glBindBuffer(_type, _buffer);
    }

    void Buffer::unbindBuffer()
    {
        glBindBuffer(_type, 0);
    }

    void Buffer::setSize(GLsizeiptr SIZE)
    {
        if(glIsBuffer(_buffer) == GL_TRUE)
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
